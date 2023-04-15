#ifndef GPTINTERFACE_REQUESTHANDLER_H
#define GPTINTERFACE_REQUESTHANDLER_H

#include <curl/curl.h>
#include "openai.hpp"
#include <QObject>
#include <QJsonArray>
#include <QtNetwork/QNetworkAccessManager>

class RequestHandler : public QObject
{
    Q_OBJECT

public:
    explicit RequestHandler(QObject* parent = nullptr);
    void startStreaming(const std::string& input);

    void addMessage(const QString &role, const QString& content);

signals:
    void newDataReceived(const QString& data);

    void responseFinshed();

public slots:
    void onReadyRead();
    void onFinished();


private:
    QNetworkAccessManager* networkManager;
    QJsonArray m_messages;
    QString m_fullResponse;
};


#endif //GPTINTERFACE_REQUESTHANDLER_H