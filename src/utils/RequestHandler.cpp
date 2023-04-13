#include <QUrl>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include "RequestHandler.h"


    RequestHandler::RequestHandler(QObject* parent) : QObject(parent),
    networkManager(new QNetworkAccessManager(this))
    {

    }

    void RequestHandler::startStreaming(const std::string& input)
    {
        QUrl url("https://api.openai.com/v1/chat/completions");
        QNetworkRequest request(url);
        QByteArray openaiApiKey = qgetenv("OPENAI_API_KEY");

        // Set your API key, streaming flag, and any other headers required by the OpenAI API
        request.setRawHeader("Content-Type", "application/json");
        request.setRawHeader("Authorization", QByteArray("Bearer ").append
        (openaiApiKey));
        // Create a JSON object for the request body
        QJsonObject requestBody;
        requestBody["model"] = "gpt-3.5-turbo";
        QVariantMap message;
        message["role"] = "user";
        message["content"] = QString::fromStdString(input);
        requestBody["messages"] = QJsonArray::fromVariantList({QVariant(message)});
        requestBody["max_tokens"] = 500;
        requestBody["temperature"] = 0;
        requestBody["stream"] = true;


        // Convert the JSON object to a QByteArray
        QByteArray jsonData = QJsonDocument(requestBody).toJson();

        QNetworkReply* reply = networkManager->post(request, jsonData);
        connect(reply, &QNetworkReply::readyRead, this, &RequestHandler::onReadyRead);
        connect(reply, &QNetworkReply::finished, this,
             &RequestHandler::onFinished); // Add this line
    }


    void RequestHandler::onReadyRead() {
        QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
        if (reply) {
            QByteArray data = reply->readAll();
            QTextStream stream(data);

            while (!stream.atEnd()) {
                QString line = stream.readLine();
                if (line.startsWith("data:")) {
                    QString eventData = line.mid(5).trimmed();
                    if (eventData == "[DONE]") {
                        qDebug() << "Stream terminated";
                        reply->abort();
                    } else {
                        QJsonDocument jsonDoc = QJsonDocument::fromJson
                                (eventData.toUtf8());
                        QJsonObject jsonObject = jsonDoc.object();
                        QJsonArray choices = jsonObject["choices"].toArray();
                        QString responseText = choices[0].toObject()["delta"]
                                .toObject()["content"].toString();
                        qDebug() << "Received data: " << responseText;
                        // Process the data as needed
                        emit RequestHandler::newDataReceived(responseText);
                    }
                }
            }
        }
    }

void RequestHandler::onFinished() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply) {
        qDebug() << "Request finished";
        reply->deleteLater();
    }
}

