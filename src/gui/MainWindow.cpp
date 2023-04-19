#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QTabBar>
#include <QVBoxLayout>
#include <QScreen>
#include "../utils/GlobalMediator.h"
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
        m_screen = QGuiApplication::primaryScreen();
        int sideWidgetWidth = static_cast<int>(m_screen->size().width() * .02);

        /*Create the parent most widget and vertical layout*/
        m_verticalWidget = new QWidget(this);
        m_verticalLayout = new QVBoxLayout(m_verticalWidget);
        m_verticalLayout->setContentsMargins(10,0,10,0);

        /*Create the horizontal layout and widget*/
        auto *horizontalWidget = new QWidget(m_verticalWidget);
        m_verticalLayout->addWidget(horizontalWidget);

        /* set up bottom bar */
        iniBottomBar();

        m_verticalWidget->setLayout(m_verticalLayout);
        auto *horizontalLayout = new QHBoxLayout(horizontalWidget);

        // Create the left column
        m_leftWidget = new QWidget(horizontalWidget);
        m_leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_leftWidget->setFixedWidth(sideWidgetWidth);
        auto* leftLayout = new QHBoxLayout(m_leftWidget);
        horizontalLayout->addWidget(m_leftWidget, 0);

        // Create center column
        m_tabWidget = new WSTabWidget(horizontalWidget);
        GlobalMediator::instance()->setWSTabWidget(m_tabWidget);
        horizontalLayout->addWidget(m_tabWidget, 0);

        // Create the right column
        m_rightToolBar = new RightToolBar(horizontalWidget);
        m_rightToolBar->setFixedWidth(sideWidgetWidth);
        horizontalLayout->addWidget(m_rightToolBar, 0, Qt::AlignRight);

        //set central widget
        setCentralWidget(m_verticalWidget);




        connect(m_rightToolBar, &RightToolBar::sendButtonClick, m_tabWidget,
                &WSTabWidget::handleSendButtonClicked);

        connect(
                GlobalMediator::instance(), &GlobalMediator::sendInputTokenCount,
                m_bottomToolBar, &BottomToolBar::setCurrentInputTokens
        );
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }


    void MainWindow::iniBottomBar()
    {
        int bottomWidgetHeight = static_cast<int>(m_screen->size().height()*.04);
        auto* btmContent = new QWidget(m_verticalWidget);
        auto* btmLayout = new QHBoxLayout(btmContent);
        btmLayout->setContentsMargins(0,0,0,0);
        m_bottomToolBar = new BottomToolBar(btmContent);
        btmLayout->addWidget(m_bottomToolBar);
        btmContent->setLayout(btmLayout);
        m_bottomToolBar->setFixedHeight(bottomWidgetHeight);
        btmContent->setObjectName("Outer");
        btmContent->setStyleSheet("#Outer { border:1px solid black; }");
        m_verticalLayout->addWidget(btmContent);
        btmContent->setFixedHeight(bottomWidgetHeight);
        GlobalMediator::instance()->setBottomToolBar(m_bottomToolBar);
    }

} // Ui
