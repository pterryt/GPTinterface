#ifndef GPTINTERFACE_GLOBALMEDIATOR_H
#define GPTINTERFACE_GLOBALMEDIATOR_H

#include <QObject>

class RightToolBar;
class BottomToolBar;
class WSTabWidget;
class LeftToolBar;
class Espnet2Encoder;
//class MediaQueue;

class GlobalMediator : public QObject
{
Q_OBJECT

public:

    static GlobalMediator* instance();
    static GlobalMediator* create();
    ~GlobalMediator() = default;
    GlobalMediator(const GlobalMediator &) = delete;
    GlobalMediator& operator=(const GlobalMediator &) = delete;

    GlobalMediator* setLeftToolBar(LeftToolBar* ltb);
    GlobalMediator* setRightToolBar(RightToolBar* rtb);
    GlobalMediator* setBottomToolBar(BottomToolBar* btb);
    GlobalMediator* setWSTabWidget(WSTabWidget* wstw);
//    GlobalMediator* setMediaPlayer(MediaQueue* mp);
    GlobalMediator* setEspnet2Encoder(Espnet2Encoder* espEnc);

    LeftToolBar* getLeftToolBar();
    RightToolBar* getRightToolBar();
    BottomToolBar* getBottomToolBar();
    WSTabWidget* getWSTabWidget();
//    MediaQueue* getMediaPlayer();
    Espnet2Encoder* getEspnet2Encoder();

    Q_SIGNALS:
    void sendInputTokenCount(int count);
    void sendHistoryButtonClicked(QString& file);

public Q_SLOTS:

private:

    inline static GlobalMediator *m_mediator = nullptr;
    explicit GlobalMediator(QObject *parent = nullptr);

    LeftToolBar *m_leftToolBar;
    RightToolBar *m_rightToolBar;
    BottomToolBar *m_bottomToolBar;
    WSTabWidget *m_tabWidget;
//    MediaQueue *m_mediaPlayer;
    Espnet2Encoder *m_espEncoder;



};

#endif // GPTINTERFACE_GLOBALMEDIATOR_H
