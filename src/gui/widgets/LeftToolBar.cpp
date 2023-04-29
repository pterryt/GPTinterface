#include "LeftToolBar.h"
#include <QShortcut>

LeftToolBar::LeftToolBar(QWidget *parent)
        : QWidget(parent)
{
    QIcon icon = QIcon("../icon/history.png");

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(5);
    m_historyButton = new QPushButton(this);
    m_historyButton->setIcon(icon);
    m_historyButton->setIconSize(QSize(22,22));
    m_layout->addWidget(m_historyButton);
    m_layout->addStretch();
    m_layout->setContentsMargins(0,0,0,1);
    setLayout(m_layout);

}

/**
* Match button height to width on resizing.
*/
void LeftToolBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_historyButton->width() > m_historyButton->height())
    {
        int nHeight = m_historyButton->width();
        m_historyButton->setFixedHeight(nHeight);
    }
}

