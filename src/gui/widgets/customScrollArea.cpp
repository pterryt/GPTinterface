#include "customScrollArea.h"

customScrollArea::customScrollArea(QWidget *parent)
        : QScrollArea(parent)
{
    QWidget *scrollAreaContent = new QWidget(this);
    setWidget(scrollAreaContent);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);


    m_vLayout = new QVBoxLayout(scrollAreaContent);
    m_vLayout->setSpacing(0);
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayout->addStretch();
//    setLayout(m_vLayout);


    QSpacerItem *spacer =
            new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_vLayout->addItem(spacer);
}

void customScrollArea::addCustomWidget(QWidget *widget)
{
    m_vLayout->insertWidget(m_vLayout->count() - 2, widget);
    m_vLayout->setStretchFactor(widget, 1);
}
