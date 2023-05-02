#ifndef GPTINTERFACE_WSTABWIDGET_H
#define GPTINTERFACE_WSTABWIDGET_H
#define QT_NO_KEYWORDS

#include <QTabWidget>
#include <QTabBar>
#include <QKeyEvent>
#include "../Workspace.h"


class RenameLineEdit;

class WSTabWidget : public QTabWidget
{
Q_OBJECT

public:

    explicit WSTabWidget(QWidget *parent = nullptr);

    Workspace *getCurrentWorkspace();

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

    /**
    * Unhides and setups the line edit for changing tab text.
     * @param index : Index of the tab that was clicked.
    */
    void handleTabDoubleClicked(int index);

private:

    Workspace *m_currentWorkspace = nullptr;
    int MAX_TABS = 8;

    /* Keeps track of the last tab doubled so it can be changed via RenameLineEdit. */
    int m_lastIndexEdit = 0;

    /* Keeps track of the workspace count for filing. */
    int m_wsCount = 0;


    void initialize();

    void initStyle();

    RenameLineEdit *m_renameLineEdit;
private Q_SLOTS:
    void handleRename();

};


class RenameLineEdit : public QLineEdit
{
Q_OBJECT

public:

    explicit RenameLineEdit(QWidget *parent) : QLineEdit(parent)
    {
        setGeometry(0, 0, 100, 20);
        hide();
    }
    Q_SIGNALS:
    void sendEnterPressed();

protected:
    void focusOutEvent(QFocusEvent *event) override
    {
        hide();
        QWidget::focusOutEvent(event);
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Return)
        {
            hide();
            Q_EMIT sendEnterPressed();
        }
        else
        {
            QLineEdit::keyPressEvent(event);
        }
    }

private:
};

#endif // GPTINTERFACE_WSTABWIDGET_H
