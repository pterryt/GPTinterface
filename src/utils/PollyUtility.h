#ifndef GPTINTERFACE_POLLYUTILITY_H
#define GPTINTERFACE_POLLYUTILITY_H

#include <aws/core/Aws.h>
#include <aws/polly/PollyClient.h>
#include <aws/crt/Api.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include "MediaQueue.h"
#include <QString>

class PollyUtility
{
public:

    PollyUtility();

    ~PollyUtility();

    bool synthesizeSpeech(const QString &text);

    void addText(const QString &text);
    void startProcessing();
    void stopProcessing();

private:

    MediaQueue *m_mediaQueue;
    bool checkLanguage(const std::string &input);
    void processTexts();

    std::deque<QString> m_texts;
    std::mutex m_textsMutex;
    std::condition_variable m_textsCv;
    std::atomic<bool> m_stopProcessing{false};
};

#endif //GPTINTERFACE_POLLYUTILITY_H