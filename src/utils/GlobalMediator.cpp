#include "GlobalMediator.h"

GlobalMediator::GlobalMediator(QObject *parent)
        : QObject(parent)
{
    m_bottomToolBar = nullptr;
    m_tabWidget = nullptr;
    m_rightToolBar = nullptr;
//    m_mediaPlayer = nullptr;
    m_espEncoder = nullptr;
}

GlobalMediator *GlobalMediator::instance()
{
    return m_mediator;
}

GlobalMediator *GlobalMediator::create()
{
    m_mediator = new GlobalMediator;
    return m_mediator;
}

GlobalMediator *GlobalMediator::setRightToolBar(RightToolBar *rtb)
{
    m_rightToolBar = rtb;
    return m_mediator;
}

GlobalMediator *GlobalMediator::setBottomToolBar(BottomToolBar *btb)
{
    m_bottomToolBar = btb;
    return m_mediator;
}

GlobalMediator *GlobalMediator::setWSTabWidget(WSTabWidget *wstw)
{
    m_tabWidget = wstw;
    return m_mediator;
}

GlobalMediator *GlobalMediator::setEspnet2Encoder(Espnet2Encoder *espEnc)
{
    m_espEncoder = espEnc;
    return m_mediator;
}

RightToolBar *GlobalMediator::getRightToolBar()
{
    return m_rightToolBar;
}

BottomToolBar *GlobalMediator::getBottomToolBar()
{
    return m_bottomToolBar;
}

WSTabWidget *GlobalMediator::getWSTabWidget()
{
    return m_tabWidget;
}


Espnet2Encoder *GlobalMediator::getEspnet2Encoder()
{
    return m_espEncoder;
}

GlobalMediator *GlobalMediator::setLeftToolBar(LeftToolBar *ltb)
{
    m_leftToolBar = ltb;
    return m_mediator;
}

LeftToolBar *GlobalMediator::getLeftToolBar()
{
    return m_leftToolBar;
}

void GlobalMediator::handleApplicationShuttingDown()
{
    m_shuttingDown = true;
}

bool GlobalMediator::isMShuttingDown() const
{
    return m_shuttingDown;
}

GlobalMediator *GlobalMediator::setScScrollArea(scScrollArea *scsa)
{
    m_scScrollArea = scsa;
    return m_mediator;
}

scScrollArea *GlobalMediator::getScScrollArea()
{
    return m_scScrollArea;
}

//GlobalMediator *GlobalMediator::setMediaPlayer(MediaQueue *mp)
//{
//    m_mediaPlayer = mp;
//    return m_mediator;
//}
//
//MediaQueue *GlobalMediator::getMediaPlayer()
//{
//    return m_mediaPlayer;
//}
