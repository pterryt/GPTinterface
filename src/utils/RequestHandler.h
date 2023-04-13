#ifndef GPTINTERFACE_REQUESTHANDLER_H
#define GPTINTERFACE_REQUESTHANDLER_H

#include <curl/curl.h>
#include "openai.hpp"
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class RequestHandler : public QObject
{
    Q_OBJECT

public:
    explicit RequestHandler(QObject* parent = nullptr);
    void startStreaming(const std::string& input);

signals:
    void newDataReceived(const QString& data);

public slots:
    void onReadyRead();
    void onFinished();

private:
    QNetworkAccessManager* networkManager;
};


#endif //GPTINTERFACE_REQUESTHANDLER_H