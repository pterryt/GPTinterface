#include "RequestHandler.h"
#include <QUrl>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>

#include "../devtools/logger.h"
#include "GlobalMediator.h"

RequestHandler::RequestHandler(QObject *parent) :
        QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    scSettings = new QHash<QUuid, int>();
}

RequestHandler::~RequestHandler()
{
    delete scSettings;
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

void RequestHandler::startStreaming(int tokens, const QString &input)
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
    requestBody["messages"] = scSettings->isEmpty() ? m_messages : addStaticContexts(m_messages);
    requestBody["max_tokens"] = limit;
    requestBody["temperature"] = 0;
    requestBody["stream"] = true;


    // Convert the JSON object to a QByteArray
    QByteArray jsonData = QJsonDocument(requestBody).toJson();
//        qDebug() << jsonData;

    QNetworkReply *reply = networkManager->post(request, jsonData);
    connect(reply, &QNetworkReply::readyRead, this, &RequestHandler::onReadyRead);
    connect(reply, &QNetworkReply::finished, this,
            &RequestHandler::onFinished); // Add this line
}


void RequestHandler::onReadyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply)
    {
        QByteArray data = reply->readAll();
        QTextStream stream(data);

        while (!stream.atEnd())
        {
            QString line = stream.readLine();
//                qDebug() << line;
            if (line.startsWith("data:"))
            {
                QString eventData = line.mid(5).trimmed();
                if (eventData == "[DONE]")
                {
//                        qDebug() << "Stream terminated";
                    try
                    {
                        reply->abort();
                    }
                    // (5/9/23) TODO: FIX THIS
                    catch (...)
                    {
                        
                    }
                }
                else
                {
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

void RequestHandler::onFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply)
    {
        int tokens = TikTokenEncoder::encode(m_fullResponse.toStdString());
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
    giLog::consoleLog->info("Calculated Response Limit: {}", limit);
    return limit;
}

void RequestHandler::clearContext()
{
    contextContainer.currentContext.clear();
    contextContainer.size = 0;
    while (!m_messages.isEmpty())
    {
        m_messages.removeAt(0);
    }
    Q_EMIT sendContextTokensCalculated(0);
}

QJsonArray RequestHandler::addStaticContexts(QJsonArray array)
{
    // (5/20/23) TODO: unnecessary container
    for (auto &sc : scSettings->keys())
    {
        QJsonObject newobj;
        newobj["role"] = "user";
        int index = scSettings->value(sc);
        switch (index)
        {
            case 0:
                newobj["content"] = GlobalMediator::instance()->getScScrollArea()->getscUOMap()->value(sc)->getText();
                array.push_front(newobj);
                break;
            case 1:
                newobj["content"] = GlobalMediator::instance()->getScScrollArea()->getscUOMap()->value(sc)->getText();
                array.push_back(newobj);
                break;
            default:
                break;
        }
    }

    return array;
}

