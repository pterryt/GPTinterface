#ifndef GPTINTERFACE_WSTABWIDGET_H
#define GPTINTERFACE_WSTABWIDGET_H
#include <iostream>
#define QT_NO_KEYWORDS
#include <QTabWidget>
#include <QTabBar>
#include "../Workspace.h"

class WSTabWidget : public QTabWidget
{
Q_OBJECT

public:

    explicit WSTabWidget(QWidget *parent = nullptr);

    Workspace* getCurrentWorkspace();

public Q_SLOTS:

    void handleTabBarClicked(int index);

    void newTab();

    void handleSendButtonClicked();

private:

    int MAX_TABS = 8;

};

#endif // GPTINTERFACE_WSTABWIDGET_H
