#include "HistoryButtonMenu.h"
#include "../../../utils/GlobalMediator.h"

HistoryButtonMenu::HistoryButtonMenu(QWidget *parent)
        : QMenu(parent)
{
    deleteButton = new QAction("Delete", this);
    addAction(deleteButton);
}