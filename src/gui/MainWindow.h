#ifndef GPTINTERFACE_MAINWINDOW_H
#define GPTINTERFACE_MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVariant>
#include <QTabBar>
#include <iostream>
#include "widgets/RightToolBar.h"
#include "Workspace.h"
#include "widgets/WSTabWidget.h"

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

    public slots:

    protected:

    private:
        Ui::mainwindow *ui{};
        WSTabWidget *m_tabWidget;
        RightToolBar *m_rightToolBar;
        QWidget *m_leftWidget;
        int MAX_TABS = 8;

    };
} // Ui

#endif //GPTINTERFACE_MAINWINDOW_H
