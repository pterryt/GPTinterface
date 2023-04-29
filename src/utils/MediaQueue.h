#ifndef GPTINTERFACE_MEDIAQUEUE_H
#define GPTINTERFACE_MEDIAQUEUE_H

#include <QObject>
#include <QVector>
#include <QMediaPlayer>
#include <mutex>
#include <condition_variable>

class MediaQueue : public QObject
{
Q_OBJECT

public:
    explicit MediaQueue(QObject *parent = nullptr);

    void addMedia(const QUrl &url);
    void clearQueue();
    void playNext();
    QMediaPlayer *m_mediaPlayer;

private Q_SLOTS:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handlePlaybackStateChanged(QMediaPlayer::PlaybackState state);

private:
    QVector<QUrl> m_mediaQueue;
    int m_currentIndex;

    std::condition_variable m_queueCv;
    std::mutex m_queueMutex;
};


#endif // GPTINTERFACE_MEDIAQUEUE_H
