#ifndef GPTINTERFACE_MAINWINDOW_H
#define GPTINTERFACE_MAINWINDOW_H
#include <iostream>
#define QT_NO_KEYWORDS
#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QTabBar>

#include "Workspace.h"
#include "widgets/RightToolBar.h"
#include "widgets/WSTabWidget.h"
#include "widgets/BottomToolBar.h"

namespace Ui
{
    QT_BEGIN_NAMESPACE
    namespace Ui
    {
        class mainwindow;
    }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow
    {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow() override;

        Q_SIGNALS:
        void resized();

    public Q_SLOTS:

        void unregisterCurrentWorkspace();
        void registerCurrentWorkspace();

    protected:
        void resizeEvent(QResizeEvent *event) override
        {
        QMainWindow::resizeEvent(event);
        Q_EMIT resized();
        };

        void keyPressEvent(QKeyEvent *event) override;

    private:
        Ui::mainwindow *ui{};
        Workspace *m_currentWorkspace = nullptr;
        WSTabWidget *m_tabWidget;
        RightToolBar *m_rightToolBar;
        BottomToolBar *m_bottomToolBar;
        QWidget *m_leftWidget;
        QScreen *m_screen;
        QVBoxLayout *m_verticalLayout;
        QWidget *m_verticalWidget;
        QHBoxLayout * m_horizontalLayout;
        QWidget *m_horizontalWidget;

        QWidget *rtContent;

        int m_sideWidgetWidth;
        int MAX_TABS = 8;

        void iniBottomBar();
        void iniRightBar();
        void iniLeftBar();

        void setSidebarHeight();
    };
} // Ui

#endif //GPTINTERFACE_MAINWINDOW_H
