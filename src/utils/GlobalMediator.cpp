#include "GlobalMediator.h"

GlobalMediator::GlobalMediator(QObject *parent)
        : QObject(parent),
        m_currentTab(0)
{

}


GlobalMediator& GlobalMediator::instance()
{
    static GlobalMediator instance;
    return instance;
}

int GlobalMediator::getActiveTabIndex() const
{
    return m_currentTab;
}

void GlobalMediator::setActiveTabIndex(int index)
{
    m_currentTab = index;
}
