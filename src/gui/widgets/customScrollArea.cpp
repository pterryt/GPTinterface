#include "customScrollArea.h"

customScrollArea::customScrollArea(QWidget *parent)
        : QScrollArea(parent)
{
    setContentsMargins(0,0,0,0);
    QWidget *scrollAreaContent = new QWidget(this);
    setWidget(scrollAreaContent);
    scrollAreaContent->setContentsMargins(0,0,0,0);
    scrollAreaContent->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Preferred);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    QSpacerItem *spacer =
            new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_vLayout = new QVBoxLayout(scrollAreaContent);
    m_vLayout->addItem(spacer);
    m_vLayout->setSpacing(0);
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayout->addStretch();
    scrollAreaContent->setLayout(m_vLayout);


}

void customScrollArea::addCustomWidget(QWidget *widget)
{
    m_vLayout->insertWidget(m_vLayout->count() - 2, widget);
    widget->setFixedWidth(size().width());
//    m_vLayout->setStretchFactor(widget, 1);
}
