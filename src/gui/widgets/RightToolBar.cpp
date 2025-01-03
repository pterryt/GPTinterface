#include "RightToolBar.h"
#include <QShortcut>
#include <QAction>
#include <QCoreApplication>
#include "../../utils/GlobalMediator.h"

/**
* Holds Send button, mic button, and prefixes button.
*/
RightToolBar::RightToolBar(QWidget *parent)
        : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QIcon sendIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/send-message.png");
    QIcon micIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/microphone.png");
    QIcon settingsIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/menu.png");
    QIcon clearContextIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/trash.png");

    m_layout = new QVBoxLayout(this);

    m_layout->setSpacing(5);
    m_layout->addStretch();


    m_clearContextButton = new QPushButton(this);
    m_layout->addWidget(m_clearContextButton);
    m_clearContextButton->setIcon(clearContextIcon);
    m_clearContextButton->setIconSize(QSize(20,20));


    m_optionsButton = new QPushButton(this);
    m_layout->addWidget(m_optionsButton);
    m_optionsButton->setIcon(settingsIcon);
    m_optionsButton->setIconSize(QSize(22,22));

    m_micButton = new QPushButton(this);
    m_layout->addWidget(m_micButton);
    m_micButton->setIcon(micIcon);
    m_micButton->setIconSize(QSize(22,22));

    m_sendButton = new QPushButton(this);
    m_layout->addWidget(m_sendButton);
    m_sendButton->setIcon(sendIcon);
    m_sendButton->setIconSize(QSize(20,20));

    m_layout->setContentsMargins(0,0,0,1);
    setLayout(m_layout);

    connect(
            m_sendButton, &QPushButton::clicked,
            this, &RightToolBar::handleSendButtonClicked);

    connect(
            m_clearContextButton, &QPushButton::clicked,
            this, &RightToolBar::handleClearContextButtonClicked);
    connect(
            m_optionsButton, &QPushButton::clicked,
            this, &RightToolBar::handleStaticContextMenuClicked);
}

/**
* Match button height to width on resizing.
*/
void RightToolBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_sendButton->width() > m_sendButton->height())
    {
        int nHeight = m_sendButton->width();
        m_sendButton->setFixedHeight(nHeight);
        m_micButton->setFixedHeight(nHeight);
        m_optionsButton->setFixedHeight(nHeight);
        m_clearContextButton->setFixedHeight(nHeight);
    }
}

/**
* Emits a signal to to MainWindow -> WSTabWidget -> Workspace
*/
void RightToolBar::handleSendButtonClicked()
{
    Q_EMIT sendButtonClick();
}

/**
* Emits a signal to to MainWindow -> WSTabWidget -> Workspace
*/
void RightToolBar::handleClearContextButtonClicked()
{
    Q_EMIT clearContextButtonClick();
}

void RightToolBar::handleStaticContextMenuClicked()
{
    GlobalMediator::instance()->sendStaticContextMenuButtonClicked();
}
