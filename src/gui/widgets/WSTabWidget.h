#ifndef GPTINTERFACE_WSTABWIDGET_H
#define GPTINTERFACE_WSTABWIDGET_H
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

    /**
    * Signal that sends token counts to reach the BottomToolBar.
    * @param input  : The current token count of the text in the inputBox.
    * @param context : The current sum token count of the context.
    */
    void sendTokenCounts(int input, int context);
    /**
     * Signal that is emitted when the current tab/Workspace changes. */
    void sendCurrentWorkspaceChanged();


public Q_SLOTS:

    /**
     * Handles new tab creation when clicking on the "+" tab.
     * @param index : Index of the tab that was clicked. Zero-based indexing. */
    void handleNewTabClicked(int index);

    /**
    * Handles tab switching. When switching to the "+" tab, the first tab
     * is selected.
    * @param index : Index of the tab that was clicked. Zero-based indexing.
    */
    void handleTabChanged(int index);

    /**
    * Adds a new tab, moves it behind the "+" tab, and focuses it.
    */
    void newTab();
    void handleSendButtonClicked();


private:

    Workspace *m_currentWorkspace = nullptr;
    int MAX_TABS = 8;

    void initialize();
    void initStyle();

protected:
};

#endif // GPTINTERFACE_WSTABWIDGET_H
