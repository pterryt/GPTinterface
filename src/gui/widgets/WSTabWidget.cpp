#include "WSTabWidget.h"

WSTabWidget::WSTabWidget(QWidget *parent)
        : QTabWidget(parent)
{
    addTab(new QWidget(this), QString::fromStdString("+"));
    newTab();


    // connect clicking on end tab to new tab creation
    connect(tabBar(), &QTabBar::tabBarClicked, this,
            &WSTabWidget::handleTabBarClicked);
}

void WSTabWidget::handleTabBarClicked(int index)
{
    if (index == count() - 1)
    {
        newTab();
    }
}

void WSTabWidget::newTab()
{
    if ((count() - 1) < MAX_TABS)
    {
        QTabBar* tabBar = this->tabBar();
        auto *x = new Workspace;
        addTab(x, QString::number(count()));
        tabBar->moveTab((count() - 1), (count() - 2));
        setCurrentIndex(count() - 2);
    }
}

void WSTabWidget::handleSendButtonClicked()
{
    Workspace *currentWorkspace = getCurrentWorkspace();
    if(currentWorkspace)
    {
       currentWorkspace->handleSendButtonClicked();
    }
}


Workspace* WSTabWidget::getCurrentWorkspace()
{
    return qobject_cast<Workspace *>(this->currentWidget());
}