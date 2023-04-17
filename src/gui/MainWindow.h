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

    public Q_SLOTS:
        void updateTokenLabels(int index);

    protected:

    private:
        Ui::mainwindow *ui{};
        WSTabWidget *m_tabWidget;
        RightToolBar *m_rightToolBar;
        BottomToolBar *m_bottomToolBar;
        QWidget *m_leftWidget;
        int MAX_TABS = 8;

    };
} // Ui

#endif //GPTINTERFACE_MAINWINDOW_H
