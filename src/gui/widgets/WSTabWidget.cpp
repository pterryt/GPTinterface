#include "WSTabWidget.h"

WSTabWidget::WSTabWidget(QWidget *parent)
        : QTabWidget(parent)
{
    addTab(new QWidget(this), QString::fromStdString("+"));
    newTab();
    m_currentWorkspace = qobject_cast<Workspace *>
            (this->currentWidget());


    /* setup font */
    QFont font = QFont("JetBrains Mono");
    font.setPointSize(14);
    tabBar()->setFont(font);

    // connect clicking on end tab to new tab creation
    connect(
            tabBar(), &QTabBar::tabBarClicked, this,
            &WSTabWidget::handleNewTabClicked);

    connect(
            this, &WSTabWidget::currentChanged, this, &WSTabWidget::handleTabChanged
            );

}

void WSTabWidget::handleNewTabClicked(int index)
{
    if (index == count() - 1)
    {
        newTab();
    }
}

void WSTabWidget::handleTabChanged(int index)
{
    if (index == count() - 1)
    {
        setCurrentIndex(0);
    }
    m_currentWorkspace = qobject_cast<Workspace *>
            (this->currentWidget());

    if (m_currentWorkspace)
    {
        /* Change the member to a shared pointer if we send this more often. */
        Q_EMIT sendCurrentWorkspaceChanged();

        Q_EMIT WSTabWidget::sendTokenCounts(m_currentWorkspace->getInputCount(),
                                       m_currentWorkspace->getContextCount());
    }


}

void WSTabWidget::newTab()
{
    if ((count() - 1) < MAX_TABS)
    {
        QTabBar* tabBar = this->tabBar();
        auto *x = new Workspace;
        m_currentWorkspace = x;
        addTab(x, QString::number(count()));
        tabBar->moveTab((count() - 1), (count() - 2));
        setCurrentIndex(count() - 2);
    }
}


void WSTabWidget::handleSendButtonClicked()
{

    if(m_currentWorkspace)
    {
       m_currentWorkspace->handleSendButtonClicked();
    }
}

Workspace *WSTabWidget::getCurrentWorkspace()
{
    return m_currentWorkspace;
}
