#include "PollyUtility.h"

#include <aws/polly/model/SynthesizeSpeechRequest.h>
#include <aws/polly/model/SynthesizeSpeechResult.h>
#include <aws/core/utils/Outcome.h>
#include <iostream>
#include <fstream>
#include <mutex>


PollyUtility::PollyUtility()
{
    m_mediaQueue = new MediaQueue();
}

PollyUtility::~PollyUtility()
{
    delete m_mediaQueue;
    m_mediaQueue = nullptr;
}

bool PollyUtility::synthesizeSpeech(const QString &text)
{
    Aws::Polly::PollyClient pollyClient_;
    std::string textString = text.toStdString();
    bool isEnglish = checkLanguage(textString);

    std::string outputFile = "audio_clips/" + textString + ".mp3";
    auto url = QUrl::fromLocalFile(QString::fromStdString(outputFile));

    Aws::Polly::Model::SynthesizeSpeechRequest request;
    request.SetOutputFormat(Aws::Polly::Model::OutputFormat::mp3);
    request.SetEngine(Aws::Polly::Model::Engine::neural);
    request.SetText(textString.c_str());
    request.SetVoiceId(
            isEnglish ?
            Aws::Polly::Model::VoiceId::Joanna :
            Aws::Polly::Model::VoiceId::Tomoko);

    auto outcome = pollyClient_.SynthesizeSpeech(request);

    if (outcome.IsSuccess())
    {
        auto &result = outcome.GetResult();
        auto &audioStream = result.GetAudioStream();
        std::ofstream output(outputFile, std::ios::out | std::ios::binary);
        output << audioStream.rdbuf();
        std::cout << "Audio saved to " << outputFile << std::endl;
        m_mediaQueue->addMedia(url);
        m_mediaQueue->playNext();
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
    else if ((unicode_value >= 0x0041 && unicode_value <= 0x005A) || (unicode_value >= 0x0061 && unicode_value <= 0x007A))
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
        else if ((unicode_value >= 0x0041 && unicode_value <= 0x005A) || (unicode_value >= 0x0061 && unicode_value <= 0x007A))
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

void PollyUtility::addText(const QString &text)
{
    std::unique_lock<std::mutex> lock(m_textsMutex);
    m_texts.push_back(text);
    m_textsCv.notify_one();
}

void PollyUtility::startProcessing()
{
    m_stopProcessing = false;
    std::thread(&PollyUtility::processTexts, this).detach();
}

void PollyUtility::stopProcessing()
{
    m_stopProcessing = true;
    m_textsCv.notify_one();
}

void PollyUtility::processTexts()
{
    while (!m_stopProcessing)
    {
        QString text;
        {
            std::unique_lock<std::mutex> lock(m_textsMutex);
            m_textsCv.wait(lock, [this]()
                           {
                               return !m_texts.empty() || m_stopProcessing;
                           });

            if (m_stopProcessing)
            {
                break;
            }

            text = m_texts.front();
            m_texts.pop_front();
        }

        synthesizeSpeech(text);
    }
}
