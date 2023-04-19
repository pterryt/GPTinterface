#include "RightToolBar.h"
#include <QShortcut>
#include <QAction>

RightToolBar::RightToolBar(QWidget *parent)
        : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setContentsMargins(0,0,0,0);

    QIcon sendIcon = QIcon("../icon/send.png");
    QIcon micIcon = QIcon("../icon/mic.png");
    QIcon settingsIcon = QIcon("../icon/settings.png");
    m_layout = new QVBoxLayout(this);

    m_layout->setSpacing(5);
    m_layout->addStretch();

    m_optionsButton = new QPushButton(this);
    m_layout->addWidget(m_optionsButton);
    m_optionsButton->setIcon(settingsIcon);

    m_micButton = new QPushButton(this);
    m_layout->addWidget(m_micButton);
    m_micButton->setIcon(micIcon);

    m_sendButton = new QPushButton(this);
    m_layout->addWidget(m_sendButton);
    m_sendButton->setIcon(sendIcon);

    m_layout->setContentsMargins(0,0,0,1);

    connect(m_sendButton, &QPushButton::clicked, this,
            &RightToolBar::handleSendButtonClicked);
}


void RightToolBar::handleSendButtonClicked()
{
    Q_EMIT sendButtonClick();
}
