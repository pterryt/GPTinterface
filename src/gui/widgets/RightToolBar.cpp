#include "RightToolBar.h"
#include <QIcon>

RightToolBar::RightToolBar(QWidget *parent)
        : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);

    m_layout->setSpacing(5);
    m_layout->addStretch();

    m_sendButton = new QPushButton(this);
    m_layout->addWidget(m_sendButton);

    m_micButton = new QPushButton(this);
    m_layout->addWidget(m_micButton);

    m_optionsButton = new QPushButton(this);
    m_layout->addWidget(m_optionsButton);

    m_layout->setContentsMargins(0,0,0,1);

}
