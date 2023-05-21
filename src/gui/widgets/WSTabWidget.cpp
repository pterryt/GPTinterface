#include "WSTabWidget.h"
#include "../../utils/GlobalMediator.h"

WSTabWidget::WSTabWidget(QWidget *parent)
        : QTabWidget(parent)
{

    /* INIT */
    initialize();
    initStyle();

    /* CONNECTIONS */
    connect(
            tabBar(), &QTabBar::tabBarClicked, this,
            &WSTabWidget::handleNewTabClicked);

    connect(
            tabBar(), &QTabBar::tabBarDoubleClicked, this, &WSTabWidget::handleTabDoubleClicked);

    connect(
            this, &WSTabWidget::currentChanged, this, &WSTabWidget::handleTabChanged);

    connect(
            m_renameLineEdit, &RenameLineEdit::sendEnterPressed, this, &WSTabWidget::handleRename);
    connect(
            this, &QTabWidget::tabCloseRequested, this, &WSTabWidget::handleCloseTab);
    connect(
            GlobalMediator::instance(), &GlobalMediator::sendHistoryButtonClicked,
            this, &WSTabWidget::handleHistoryButtonClicked);

}

void WSTabWidget::initialize()
{
    setTabsClosable(true);
    addTab(new QWidget(this), QString::fromStdString("+"));
    tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
    newTab();
    m_currentWorkspace = qobject_cast<Workspace *>(this->currentWidget());
    m_renameLineEdit = new RenameLineEdit(this);
}

void WSTabWidget::initStyle()
{
    QFont font = QFont("Arial");
    font.setPointSize(13);
    tabBar()->setFont(font);
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
        Q_EMIT sendCurrentWorkspaceChanged();

        Q_EMIT WSTabWidget::sendTokenCounts(m_currentWorkspace->getInputCount(),
                                            m_currentWorkspace->getContextCount());
    }
}

void WSTabWidget::newTab()
{
    if ((count() - 1) < MAX_TABS)
    {
        QTabBar *tabBar = this->tabBar();
        auto *x = new Workspace(m_wsCount, this);
        m_wsCount++;
        m_currentWorkspace = x;
        addTab(x, "New Empty Tab");
        tabBar->moveTab((count() - 1), (count() - 2));
        setCurrentIndex(count() - 2);

        connect(
                m_currentWorkspace, &Workspace::sendNameSet, this, [this](const QString &name) {
                    setTabText(currentIndex(), name);
                }
        );
    }
}

void WSTabWidget::handleSendButtonClicked()
{
    if (m_currentWorkspace)
    {
        m_currentWorkspace->handleSendButtonClicked();
    }
}

void WSTabWidget::handleClearContextButtonClicked()
{
    if (m_currentWorkspace)
    {
        m_currentWorkspace->handleContextClearedButtonClicked();
    }
}

Workspace *WSTabWidget::getCurrentWorkspace()
{
    return m_currentWorkspace;
}

void WSTabWidget::handleTabDoubleClicked(int index)
{
    auto currentText = tabText(index);
    m_lastIndexEdit = index;
    m_renameLineEdit->setText(currentText);

    QPoint pos = tabBar()->tabRect(index).bottomLeft();
    pos = tabBar()->mapToGlobal(pos);
    pos = this->mapFromGlobal(pos);

    m_renameLineEdit->move(pos);
    m_renameLineEdit->show();
    m_renameLineEdit->setFocus();
    m_renameLineEdit->selectAll();
}

void WSTabWidget::handleRename()
{
    setTabText(m_lastIndexEdit, m_renameLineEdit->text());
    qobject_cast<Workspace *>(widget(m_lastIndexEdit))->setName(m_renameLineEdit->text());
}

void WSTabWidget::handleHistoryButtonClicked(QPointer<HistoryButton> &button)
{
    newTab();
    m_currentWorkspace->rebuildHistoricConversation(button);
}

void WSTabWidget::handleCloseTab(int index)
{
    bool isCurrent = currentIndex() == index;
    if (count() == 2)
    {
        newTab();
    }
    delete widget(index);
    if (isCurrent)
    {
        setCurrentIndex(count() - 2);
    }
}

void WSTabWidget::handleMoveLeft()
{
    if (currentIndex() == 0)
    {
        setCurrentIndex(count() - 2);
        return;
    }
    setCurrentIndex(currentIndex() - 1);

}

void WSTabWidget::handleMoveRight()
{
    if (currentIndex() == count() - 2)
    {
        setCurrentIndex(0);
        return;
    }
    setCurrentIndex(currentIndex() + 1);
}
