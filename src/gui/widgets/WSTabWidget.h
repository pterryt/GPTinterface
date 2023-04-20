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

    Q_SIGNALS:

    void sendTokenCounts(int input, int context);
    void sendCurrentWorkspaceChanged();


public Q_SLOTS:

    void handleNewTabClicked(int index);
    void handleTabChanged(int index);

    void newTab();

    void handleSendButtonClicked();

private:

    Workspace *m_currentWorkspace = nullptr;
    int MAX_TABS = 8;

protected:
};

#endif // GPTINTERFACE_WSTABWIDGET_H
