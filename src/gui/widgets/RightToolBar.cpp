#include "RightToolBar.h"
#include <QShortcut>
#include <QAction>

RightToolBar::RightToolBar(QWidget *parent)
        : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QPixmap pixmapSend("/home/phil/_downloads/_Pictures/send-message.png");
    QIcon sendIcon = QIcon(pixmapSend);
//    QIcon micIcon = QIcon("../icon/mic.png");
    QPixmap pixmapMic("/home/phil/_downloads/_Pictures/microphone.png");
    QIcon micIcon = QIcon(pixmapMic);
    QPixmap pixmapMenu("/home/phil/_downloads/_Pictures/menu.png");
    QIcon settingsIcon = QIcon(pixmapMenu);
    m_layout = new QVBoxLayout(this);

    m_layout->setSpacing(5);
    m_layout->addStretch();

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

    connect(m_sendButton, &QPushButton::clicked, this,
            &RightToolBar::handleSendButtonClicked);
}

void RightToolBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_sendButton->width() > m_sendButton->height())
    {
        int nHeight = m_sendButton->width();
        m_sendButton->setFixedHeight(nHeight);
        m_micButton->setFixedHeight(nHeight);
        m_optionsButton->setFixedHeight(nHeight);
    }
}

void RightToolBar::handleSendButtonClicked()
{
    Q_EMIT sendButtonClick();
}
