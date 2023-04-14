#include "ToolTipEventFilter.h"
#include <QEvent>
#include <QWidget>
#include <QToolTip>
#include <QHelpEvent>

ToolTipEventFilter::ToolTipEventFilter(QObject *parent) : QObject(parent) {}

bool ToolTipEventFilter::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::ToolTip) {
        QWidget *widget = qobject_cast<QWidget *>(watched);
        if (widget) {
            QString tooltipText;
            tooltipText += "Class: " + QString(watched->metaObject()->className()) + "\n";

            if (watched->parent()) {
                tooltipText += "Parent class: " + QString(watched->parent()->metaObject()->className()) + "\n";
            }

            if (watched->parent() && watched->parent()->parent()) {
                tooltipText += "Grandparent class: " + QString(watched->parent()->parent()->metaObject()->className());
            }

            QToolTip::showText(static_cast<QHelpEvent *>(event)->globalPos(), tooltipText, widget);
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}
