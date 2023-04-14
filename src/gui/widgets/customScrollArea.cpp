#include "customScrollArea.h"

customScrollArea::customScrollArea(QWidget *parent)
        : QScrollArea(parent)
{
    m_vLayout = new QVBoxLayout(this);
    setLayout(m_vLayout);
}

void customScrollArea::addCustomWidget(QWidget *widget)
{
   m_vLayout->addWidget(widget);
}