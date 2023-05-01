#ifndef GPTINTERFACE_POLLYUTILITY_H
#define GPTINTERFACE_POLLYUTILITY_H

#include <aws/core/Aws.h>
#include <aws/polly/PollyClient.h>
#include <aws/crt/Api.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include "MediaQueue.h"
#include <QString>
#include <condition_variable>
#include <QWaitCondition>

class PollyUtility
{
public:

    PollyUtility();

    ~PollyUtility();

    bool synthesizeSpeech(int index, const QString &text);


private:

    MediaQueue *m_mediaQueue;
    bool checkLanguage(const std::string &input);
    std::condition_variable m_Cv;

};

#endif //GPTINTERFACE_POLLYUTILITY_H