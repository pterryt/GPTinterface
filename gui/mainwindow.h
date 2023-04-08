//
// Created by phil on 4/7/23.
//

#ifndef GPTINTERFACE_MAINWINDOW_H
#define GPTINTERFACE_MAINWINDOW_H

#include <QMainWindow>
#include <QTabBar>
#include "workspace.h"
namespace Ui
{
    QT_BEGIN_NAMESPACE
    namespace Ui
    {
        class mainwindow;
    }
    QT_END_NAMESPACE

    class mainwindow : public QMainWindow
    {
    Q_OBJECT

    public:
        explicit mainwindow(QWidget *parent = nullptr);

        ~mainwindow() override;

    public slots:

    void addTab(const int MAX_TABS, int& tabCount, QTabWidget* tabWidget)
    {
        if (tabCount < MAX_TABS)
        {
            workspace *x = new workspace;
            tabWidget->addTab(x, QString::number(tabCount + 1));
            tabCount++;
        }
    };

    private:
        Ui::mainwindow *ui{};
        QTabBar m_tabBar;

    };
} // Ui

#endif //GPTINTERFACE_MAINWINDOW_H
