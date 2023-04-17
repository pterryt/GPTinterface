#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QTabBar>
#include <QVBoxLayout>
#include <QScreen>
#include "widgets/RightToolBar.h"
#include "widgets/BottomToolBar.h"


namespace Ui
{
    MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::mainwindow)
    {
        /*initialize UI objects from design*/
        ui->setupUi(this);

        /*Get toolbar sizes based on percentage of screen size*/
        QScreen *screen = QGuiApplication::primaryScreen();
        int sideWidgetWidth = static_cast<int>(screen->size().width() * .015);
        int bottomWidgetHeight = static_cast<int>(screen->size().height() *
                                                  .05);

        /*Create the parent most widget and vertical layout*/
        auto *verticalWidget = new QWidget(this);
//        verticalWidget->setStyleSheet("border: 1px solid blue;");
        auto *verticalLayout = new QVBoxLayout(verticalWidget);

        /*Create the horizontal layout and widget*/
        auto *horizontalWidget = new QWidget(verticalWidget);
        verticalLayout->addWidget(horizontalWidget);


        /*Create bottom toolbar and add it to vertical layout*/
        m_bottomToolBar = new BottomToolBar(verticalWidget);
        m_bottomToolBar->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Fixed);
        m_bottomToolBar->setFixedHeight(bottomWidgetHeight);
        m_bottomToolBar->setStyleSheet("border: 1px solid red;");
        verticalLayout->addWidget(m_bottomToolBar);

        verticalWidget->setLayout(verticalLayout);
        auto *horizontalLayout = new QHBoxLayout(horizontalWidget);

        // Create the left column
        m_leftWidget = new QWidget(horizontalWidget);
        m_leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_leftWidget->setFixedWidth(sideWidgetWidth);
        auto* leftLayout = new QHBoxLayout(m_leftWidget);
        horizontalLayout->addWidget(m_leftWidget, 0);

        // Create center column
        m_tabWidget = new WSTabWidget(horizontalWidget);
        horizontalLayout->addWidget(m_tabWidget, 0);

        // Create the right column
        m_rightToolBar = new RightToolBar(horizontalWidget);
        m_rightToolBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_rightToolBar->setFixedWidth(sideWidgetWidth);
        m_rightToolBar->setContentsMargins(0,0,0,0);
        horizontalLayout->addWidget(m_rightToolBar, 0, Qt::AlignRight);

        //set central widget
        setCentralWidget(verticalWidget);

        connect(m_rightToolBar, &RightToolBar::sendButtonClick, m_tabWidget,
                &WSTabWidget::handleSendButtonClicked);

        connect(m_tabWidget, &WSTabWidget::currentChanged, this, &MainWindow::updateTokenLabels);

    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::updateTokenLabels(int index)
    {
        int sumTokens = m_tabWidget->getCurrentWorkspace()->getTotalTokens();
        int inputTokens = m_tabWidget->getCurrentWorkspace()->getInputTokens();
        m_bottomToolBar->setTokenCounts(sumTokens, inputTokens);
    }

} // Ui
