#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QTabBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "widgets/RightToolBar.h"
#include <QScreen>
#include <iostream>

namespace Ui
{
    MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::mainwindow)
    {
        ui->setupUi(this);


        // create the main vertical widget
        auto *totalWidget = new QWidget(this);
        auto *totalLayout = new QVBoxLayout(totalWidget);

        // create the center horizontal widget that holds the mainframe and
        // side toolbars
        auto *mainWidget = new QWidget(totalWidget);
        auto *mainLayout = new QHBoxLayout(mainWidget);


        QScreen *screen = QGuiApplication::primaryScreen();
        int sideWidgetWidth = static_cast<int>(screen->size().width() * .015);

        // Create the left column
        m_leftWidget = new QWidget(mainWidget);
        m_leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_leftWidget->setFixedWidth(sideWidgetWidth);
        auto* leftLayout = new QHBoxLayout(m_leftWidget);
        mainLayout->addWidget(m_leftWidget, 0);

        // Create center column
        m_tabWidget = new WSTabWidget(mainWidget);
        mainLayout->addWidget(m_tabWidget, 0);

        // Create the right column
        m_rightToolBar = new RightToolBar(mainWidget);
        m_rightToolBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_rightToolBar->setFixedWidth(sideWidgetWidth);
        m_rightToolBar->setContentsMargins(0,0,0,0);
        mainLayout->addWidget(m_rightToolBar, 0, Qt::AlignRight);

        //set central widget
        setCentralWidget(mainWidget);

        connect(m_rightToolBar, &RightToolBar::sendButtonClick, m_tabWidget,
                &WSTabWidget::handleSendButtonClicked);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

} // Ui
