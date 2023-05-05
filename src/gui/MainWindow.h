#ifndef GPTINTERFACE_MAINWINDOW_H
#define GPTINTERFACE_MAINWINDOW_H
#define QT_NO_KEYWORDS

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QTabBar>

#include <spdlog/spdlog.h>
#include "Workspace.h"
#include "widgets/RightToolBar.h"
#include "widgets/LeftToolBar.h"
#include "widgets/WSTabWidget.h"
#include "widgets/BottomToolBar.h"
#include "../utils/Espnet2Encoder.h"

namespace Ui
{
    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class mainwindow;
    }

    QT_END_NAMESPACE

    /* Class to hold all objects of the main screen. */
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow() override;

    public Q_SLOTS:

        /* Unregister the m_currentWorkspace when switching to a new tab. */
        void unregisterCurrentWorkspace();
        /* Register the new Workspace when switching to a new tab. */
        void registerCurrentWorkspace();

    protected:

        void resizeEvent(QResizeEvent *event) override;

        void keyPressEvent(QKeyEvent *event) override;

    private:

        Ui::mainwindow *ui{};
        /* Pointer to the current tab's Workspace. */
        Workspace *m_currentWorkspace = nullptr;
        /* Pointer to the WSTabWidget. */
        WSTabWidget *m_tabWidget;
        /* Pointer to the bottomToolBar. */
        BottomToolBar *m_bottomToolBar;
        /* Pointer to the primary screen. */
        QScreen *m_screen;
        /* Pointer to the main vertical layout. */
        QVBoxLayout *m_verticalLayout;
        /* Pointer to the widget that holds all vertical content. */
        QWidget *m_verticalWidget;
        /* Pointer to the main horizontal layout. */
        QHBoxLayout * m_horizontalLayout;
        /* Pointer to the widget that holds all horizontal content. */
        QWidget *m_horizontalWidget;
        /* Pointer to the pareht widget that hold the rightToolBar */
        QWidget *rightContent;
        /* Pointer to the rightToolBar. */
        RightToolBar *m_rightToolBar;
        /* Pointer to the pareht widget that hold the leftToolBar */
        QWidget *leftContent;
        /* Pointer to the leftToolBar. */
        LeftToolBar *m_leftToolBar;
        /* Pointer to the history panel holder widget. */
        QWidget *m_historyHolder;
        /* Fixed-width for both side bars. Based on a percentage of the
         * screen size. */
        int m_sideWidgetWidth;
        /* Max number of tabs. Once reached, they can no longer be created. */
        int MAX_TABS = 8;

        /* Creates parent widget, assign the bottom bar, and add styling. */
        void iniBottomBar();
        /* Creates parent widget, assign the right bar, and add styling. */
        void iniRightBar();
        /* Creates parent widget, assign the left bar, and add styling. */
        void iniLeftBar();

        /* Initialize dark style. */
        void iniTheme();

        /* Sets the left and right toolbars to match the height of the
         * tabwidget workspace by subtracting the tabbar height. */
        void setSidebarHeight();

        void cleanUpFolders(const QString& path);

    private Q_SLOTS:

        void on_actionExit_triggered();

        void handleHistoryButtonClicked();

    };
} // Ui

#endif //GPTINTERFACE_MAINWINDOW_H
