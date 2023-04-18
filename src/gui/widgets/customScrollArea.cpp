#include "customScrollArea.h"

customScrollArea::customScrollArea(QWidget *parent)
        : QScrollArea(parent)
{
    QWidget *scrollAreaContent = new QWidget(this);
    setWidget(scrollAreaContent);
    setWidgetResizable(true);


    m_vLayout = new QVBoxLayout(scrollAreaContent);
//    setLayout(m_vLayout);
    m_vLayout->setSpacing(0);
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayout->addStretch();
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);

    QSpacerItem *spacer = new QSpacerItem(0,0, QSizePolicy::Minimum,
                                          QSizePolicy::Expanding);
    m_vLayout->addItem(spacer);
}

void customScrollArea::addCustomWidget(QWidget *widget)
{
    m_vLayout->insertWidget(m_vLayout->count() - 2, widget);
//   m_vLayout->addWidget(widget);
}
