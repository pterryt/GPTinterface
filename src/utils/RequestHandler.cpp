#include "RequestHandler.h"
#include <QUrl>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include "GlobalMediator.h"

    RequestHandler::RequestHandler(QObject* parent) : QObject(parent),
    networkManager(new QNetworkAccessManager(this))
    {
        m_encoder = new TikTokenEncoder(this);
    }

    void RequestHandler::addMessage(
            int tokens, const QString &role, const QString &content)
    {
        Message message;
        message.size = tokens;
        message.msg["role"] = role;
        message.msg["content"] = content;
        contextContainer.currentContext.push_back(message);
        contextContainer.size += tokens;
        Q_EMIT sendContextTokensCalculated(contextContainer.size);
        m_messages.append(message.msg);
    }

    void RequestHandler::startStreaming(int tokens, const QString& input)
    {
        addMessage(tokens, "user", input);

        int limit = calcResponseLimit();

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
        requestBody["max_tokens"] = limit;
        requestBody["temperature"] = 0;
        requestBody["stream"] = true;


        // Convert the JSON object to a QByteArray
        QByteArray jsonData = QJsonDocument(requestBody).toJson();
//        qDebug() << jsonData;

        QNetworkReply* reply = networkManager->post(request, jsonData);
        connect(reply, &QNetworkReply::readyRead, this, &RequestHandler::onReadyRead);
        connect(reply, &QNetworkReply::finished, this,
             &RequestHandler::onFinished); // Add this line
    }


    void RequestHandler::onReadyRead()
    {
        QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
        if (reply) {
            QByteArray data = reply->readAll();
            QTextStream stream(data);

            while (!stream.atEnd()) {
                QString line = stream.readLine();
//                qDebug() << line;
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
        auto start = std::chrono::high_resolution_clock::now();
        int tokens = m_encoder->encode(m_fullResponse.toStdString());
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                (end - start);
//        qDebug() << "Tiktoken time required: " << duration.count();
        addMessage(tokens, "assistant", m_fullResponse);
        m_fullResponse = "";
        Q_EMIT responseFinshed();
        reply->deleteLater();
    }
}

int RequestHandler::calcResponseLimit()
{
    int limit = TOKEN_LIMIT - contextContainer.size;
    while (TOKEN_LIMIT - contextContainer.size < 500)
    {
        contextContainer.size -= contextContainer.currentContext.front().size;
        contextContainer.currentContext.pop_front();
        Q_EMIT sendContextTokensCalculated(contextContainer.size);
    }
    return limit;
}

