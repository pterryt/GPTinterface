#include <QTextEdit>
#include "OutputContainer.h"

OutputContainer::OutputContainer(QWidget *parent)
        : QListWidget(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setWordWrap(true);
}
