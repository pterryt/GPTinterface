#include "MediaQueue.h"

#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#include <thread>

#include <iostream>

MediaQueue::MediaQueue(QObject *parent)
        : QObject(parent), m_mediaPlayer(new QMediaPlayer(this)), m_currentIndex(-1)
{
    QAudioDevice audioDevice = QMediaDevices::defaultAudioOutput();
    m_mediaPlayer->setAudioOutput(new QAudioOutput(audioDevice, this));
    m_mediaPlayer->audioOutput()->setVolume(100);
    m_mediaQueue = new QQueue<QUrl>();

//    connect(m_mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &MediaQueue::handlePlaybackStateChanged);

    connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this,
            &MediaQueue::handleMediaStatusChanged);

    connect(this, &MediaQueue::handleNewMedia, this, &MediaQueue::addMedia);
}

void MediaQueue::addMedia()
{
    playNext();
    m_currentIndex ++;
}

void MediaQueue::clearQueue()
{
    m_mediaQueue->clear();
    m_currentIndex = -1;
}

void MediaQueue::playNext()
{
    if (m_mediaPlayer->isPlaying())
    {
        return;
    }

    if (!m_mediaQueue->isEmpty())
    {
        qDebug() << m_mediaQueue->front();
        m_mediaPlayer->setSource(m_mediaQueue->dequeue());
        m_mediaPlayer->play();
    }
}

void MediaQueue::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        playNext();
    }
}

int MediaQueue::getCurrentIndex() const
{
    return m_currentIndex;
}

MediaQueue::~MediaQueue()
{
    delete m_mediaQueue;
    m_mediaQueue = nullptr;
}

void MediaQueue::handlePlaybackStateChanged(QMediaPlayer::PlaybackState state)
{
        if (state == QMediaPlayer::PlaybackState::StoppedState)
    {
        playNext();
    }
}
