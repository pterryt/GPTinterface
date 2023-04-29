#include "MediaQueue.h"
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#include <iostream>

MediaQueue::MediaQueue(QObject *parent)
        : QObject(parent), m_mediaPlayer(new QMediaPlayer(this)), m_currentIndex(-1)
{
    QAudioDevice audioDevice = QMediaDevices::defaultAudioOutput();
    m_mediaPlayer->setAudioOutput(new QAudioOutput(audioDevice, this));
    m_mediaPlayer->audioOutput()->setVolume(100);
    connect(m_mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &MediaQueue::handlePlaybackStateChanged);
}

void MediaQueue::addMedia(const QUrl &url)
{
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_mediaQueue.append(url);
    m_queueCv.notify_one();
}

void MediaQueue::clearQueue()
{
    m_mediaQueue.clear();
    m_currentIndex = -1;
}

void MediaQueue::playNext()
{
    if (m_mediaPlayer->isPlaying())
    {
        return;
    }

    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_queueCv.wait(lock, [this] { return !m_mediaQueue.isEmpty(); });

    m_currentIndex = (m_currentIndex + 1) % m_mediaQueue.size();
    m_mediaPlayer->setSource(m_mediaQueue[m_currentIndex]);
    m_mediaPlayer->play();
}

void MediaQueue::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        playNext();
    }
}

void MediaQueue::handlePlaybackStateChanged(QMediaPlayer::PlaybackState state)
{
        if (state == QMediaPlayer::PlaybackState::StoppedState)
    {
        playNext();
    }
}
