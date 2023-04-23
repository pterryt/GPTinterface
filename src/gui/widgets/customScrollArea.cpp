#include "customScrollArea.h"
#include "textboxes/customTextEdit.h"
#include <QScrollBar>
#include <QResizeEvent>
#include <QCoreApplication>

customScrollArea::customScrollArea(QWidget *parent)
        : QScrollArea(parent)
{
    setContentsMargins(0,0,0,0);
    auto *scrollAreaContent = new QWidget(this);
    setWidget(scrollAreaContent);
    scrollAreaContent->setContentsMargins(0,0,0,0);
    scrollAreaContent->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Preferred);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    auto *spacer =
            new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_vLayout = new QVBoxLayout(scrollAreaContent);
    m_vLayout->addItem(spacer);
    m_vLayout->setSpacing(0);
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayout->addStretch();
    scrollAreaContent->setLayout(m_vLayout);

    m_vScrollBar = verticalScrollBar();

}

void customScrollArea::addCustomWidget(QWidget *widget)
{
    m_vLayout->insertWidget(m_vLayout->count() - 2, widget);
    widget->setFixedWidth(size().width());
}

void customScrollArea::updateScrollPosition()
{
    m_vScrollBar->setValue(m_vScrollBar->maximum());
}

void customScrollArea::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    int updatedWidth = event->size().width();
    for (int i = 0; i < m_vLayout->count() - 1; ++i)
    {
        customTextEdit *widget = qobject_cast<customTextEdit *>(m_vLayout->itemAt(i)
                ->widget());
        if (widget)
        {
            widget->setFixedWidth(updatedWidth);
            widget->updateSizeHint();

        }
    }
}
