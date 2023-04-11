#ifndef GPTINTERFACE_WSTABWIDGET_H
#define GPTINTERFACE_WSTABWIDGET_H

#include <QTabWidget>
#include <iostream>
#include <QTabBar>
#include "../Workspace.h"

class WSTabWidget : public QTabWidget
{
Q_OBJECT

public:

    explicit WSTabWidget(QWidget *parent = nullptr);

public slots:

    void handleTabBarClicked(int index);

    void newTab();

    void handleSendButtonClicked();

private:

    int MAX_TABS = 8;

};

#endif // GPTINTERFACE_WSTABWIDGET_H
