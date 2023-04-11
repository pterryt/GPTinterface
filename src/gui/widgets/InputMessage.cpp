#include "InputMessage.h"
#include <QListWidget>
#include <QListWidgetItem>


InputMessage::InputMessage(const QString& text, QListWidget *parent)
        : QListWidgetItem(text, parent)
{
}