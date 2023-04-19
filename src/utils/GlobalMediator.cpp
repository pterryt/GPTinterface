#include "GlobalMediator.h"

GlobalMediator::GlobalMediator(QObject *parent)
        : QObject(parent)
{
    m_bottomToolBar = nullptr;
    m_rightToolBar = nullptr;
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