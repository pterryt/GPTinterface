#ifndef GPTINTERFACE_HISTORYBUTTONMENU_H
#define GPTINTERFACE_HISTORYBUTTONMENU_H

#include <QMenu>

class HistoryButtonMenu : public QMenu
{
Q_OBJECT

public:
    explicit HistoryButtonMenu(QWidget *parent = nullptr);
    QAction* deleteButton;
};

#endif // GPTINTERFACE_HISTORYBUTTONMENU_H
