#ifndef GPTINTERFACE_REQUESTHANDLER_H
#define GPTINTERFACE_REQUESTHANDLER_H
#define QT_NO_KEYWORDS

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

#include <curl/curl.h>
#include "TikTokenEncoder.h"

class RequestHandler : public QObject
{
    Q_OBJECT

public:

    explicit RequestHandler(QObject* parent = nullptr);

    void startStreaming(int tokens, const QString &input);

    /**
    * Creates a message object and appends it to the context container.
     * @param tokens : The token cost of the message.
     * @param role : The role ( 'assistant', 'user', etc. ) that will be given
     * to the message.
     * @param content : The message text.
    */
    void addMessage(int tokens, const QString &role, const QString& content);

Q_SIGNALS:
    void newDataReceived(const QString& data);
    void responseFinshed();
    void sendContextTokensCalculated(int count);

public Q_SLOTS:
    void onReadyRead();
    void onFinished();

private:
    struct Message
    {
        QJsonObject msg;
        int size = 0;
    };

    struct ContextContainer
    {
        QVector<Message> currentContext;
        int size = 0;
    };

    QNetworkAccessManager* networkManager;
    ContextContainer contextContainer;
    QJsonArray m_messages;
    QString m_fullResponse;
    TikTokenEncoder *m_encoder;
    const int TOKEN_LIMIT = 4000; // hard limit 4096
};


#endif //GPTINTERFACE_REQUESTHANDLER_H