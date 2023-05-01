#ifndef GPTINTERFACE_MEDIAQUEUE_H
#define GPTINTERFACE_MEDIAQUEUE_H

#include <QObject>
#include <QVector>
#include <QQueue>

#include <QMediaPlayer>
#include <mutex>
#include <condition_variable>
#include <QMutex>

class MediaQueue : public QObject
{
Q_OBJECT

public:
    explicit MediaQueue(QObject *parent = nullptr);
    ~MediaQueue();

    void addMedia();
    void clearQueue();
    void playNext();
    int getCurrentIndex() const;

    QMediaPlayer *m_mediaPlayer;
    QQueue<QUrl> *m_mediaQueue;
    std::mutex m_queueMutex;

private Q_SLOTS:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handlePlaybackStateChanged(QMediaPlayer::PlaybackState state);
Q_SIGNALS:

    void handleNewMedia();

private:
    int m_currentIndex;
    std::condition_variable m_queueCv;

};


#endif // GPTINTERFACE_MEDIAQUEUE_H
