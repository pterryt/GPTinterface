#include "RightToolBar.h"
#include <QIcon>
#include <QShortcut>

RightToolBar::RightToolBar(QWidget *parent)
        : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);

    m_layout->setSpacing(5);
    m_layout->addStretch();


    m_optionsButton = new QPushButton(this);
    m_layout->addWidget(m_optionsButton);

    m_micButton = new QPushButton(this);
    m_layout->addWidget(m_micButton);

    m_sendButton = new QPushButton(this);
    m_layout->addWidget(m_sendButton);

    m_layout->setContentsMargins(0,0,0,1);

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::ShiftModifier +
            Qt::Key_Return), this);
    connect(shortcut, &QShortcut::activated, [&](){m_sendButton->click();});
    connect(m_sendButton, &QPushButton::clicked, this,
            &RightToolBar::handleSendButtonClicked);
}


void RightToolBar::handleSendButtonClicked()
{
    emit sendButtonClick();
}
