#include "RequestHandler.h"
#include <QUrl>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>


    RequestHandler::RequestHandler(QObject* parent) : QObject(parent),
    networkManager(new QNetworkAccessManager(this))
    {
        m_encoder = new TikTokenEncoder(this);
    }

    void RequestHandler::addMessage(const QString &role, const QString &content)
    {
        Message message;
        message.size = m_encoder->encode(content.toStdString());
        message.msg["role"] = role;
        message.msg["content"] = content;
        contextContainer.currentContext.push_back(message);
        contextContainer.size += message.size;
        m_messages.append(message.msg);
    }

    void RequestHandler::startStreaming(const QString& input)
    {
        addMessage("user", input);

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
        requestBody["messages"] = m_messages;
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
//                        qDebug() << "Stream terminated";
                        reply->abort();
                    } else {
                        QJsonDocument jsonDoc = QJsonDocument::fromJson
                                (eventData.toUtf8());
                        QJsonObject jsonObject = jsonDoc.object();
                        QJsonArray choices = jsonObject["choices"].toArray();
                        QString responseText = choices[0].toObject()["delta"]
                                .toObject()["content"].toString();
//                        qDebug() << "Received data: " << responseText;
                        m_fullResponse += responseText;
                        // Process the data as needed
                        Q_EMIT RequestHandler::newDataReceived(responseText);
                    }
                }
            }
        }
    }

void RequestHandler::onFinished() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply) {
//        qDebug() << "Request finished";
        addMessage("assistant", m_fullResponse);
        m_fullResponse = "";
        Q_EMIT responseFinshed();
        reply->deleteLater();
    }
}

