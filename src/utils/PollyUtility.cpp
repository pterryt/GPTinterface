#include "PollyUtility.h"

#include <aws/polly/model/SynthesizeSpeechRequest.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <QDir>

PollyUtility::PollyUtility()
{
    m_mediaQueue = new MediaQueue();
}

PollyUtility::~PollyUtility()
{
    delete m_mediaQueue;
    m_mediaQueue = nullptr;
}

bool PollyUtility::synthesizeSpeech(const int wsIndex, const int containerIndex,
                                    const int stringIndex, const QString &text)
{
    Aws::Polly::PollyClient pollyClient_;
    std::string textString = text.toStdString();
    bool isEnglish = checkLanguage(textString);

    QString dirname =
            "audio_clips/ws_" + QString::number(wsIndex) +
            "/cte_" + QString::number(containerIndex) + "/";
    QDir dir;

    if (!dir.exists(dirname))
    {
        dir.mkdir(dirname);
    }

    QString outputFile = dirname + "clip" + QString::number(stringIndex) + ".mp3";
    auto url = QUrl::fromLocalFile(outputFile);

    Aws::Polly::Model::SynthesizeSpeechRequest request;
    request.SetOutputFormat(Aws::Polly::Model::OutputFormat::mp3);
    request.SetEngine(Aws::Polly::Model::Engine::neural);
    request.SetText(textString.c_str());
    request.SetVoiceId(
            isEnglish ?
            Aws::Polly::Model::VoiceId::Joanna :
            Aws::Polly::Model::VoiceId::Tomoko);

    auto outcome = pollyClient_.SynthesizeSpeech(request);

    // (5/2/23) TODO: understand this code -> can Qobjects be used?
    if (outcome.IsSuccess())
    {
        auto &result = outcome.GetResult();
        auto &audioStream = result.GetAudioStream();

        std::ofstream output(outputFile.toStdString(), std::ios::out | std::ios::binary);

        output << audioStream.rdbuf();

        std::unique_lock<std::mutex> lock(m_mediaQueue->m_queueMutex);
        m_Cv.wait(lock, [stringIndex, this]() {
            return stringIndex == m_mediaQueue->getCurrentIndex() + 1;
        });

        m_mediaQueue->m_mediaQueue->enqueue(url);

        QMetaObject::invokeMethod(m_mediaQueue, &MediaQueue::handleNewMedia);

        m_Cv.notify_all();
        return true;
    }
    else
    {
        std::cerr << "Error: " << outcome.GetError().GetMessage() << std::endl;
        return false;
    }
}

bool PollyUtility::checkLanguage(const std::string &input)
{
    bool is_english = false;
    QChar ch = input.at(0);
    ushort unicode_value = ch.unicode();

    // Check the first character
    if (unicode_value >= 0x3040 && unicode_value <= 0x30FF)
    {
        return false;  // Japanese
    }
    else if ((unicode_value >= 0x0041 && unicode_value <= 0x005A) ||
             (unicode_value >= 0x0061 && unicode_value <= 0x007A))
    {
        is_english = true;
    }

    // Check the rest of the string
    for (int i = 1; i < input.length(); i++)
    {
        ch = input[i];
        unicode_value = ch.unicode();
        if (unicode_value >= 0x3040 && unicode_value <= 0x30FF)
        {
            return false;  // Japanese
        }
        else if ((unicode_value >= 0x0041 && unicode_value <= 0x005A) ||
                 (unicode_value >= 0x0061 && unicode_value <= 0x007A))
        {
            if (is_english)
            {
                return true;  // English
            }
            else
            {
                is_english = true;
            }
        }
        else
        {
            is_english = false;
        }
    }

    return is_english;
}

