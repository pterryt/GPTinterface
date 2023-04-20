#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QTabBar>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "../utils/GlobalMediator.h"
#include "widgets/RightToolBar.h"
#include "widgets/BottomToolBar.h"



namespace Ui
{
    MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::mainwindow)
    {
        /* INI DESIGN */
        ui->setupUi(this);

        m_screen = QGuiApplication::primaryScreen();
        m_sideWidgetWidth = static_cast<int>(m_screen->size().width() * .02);


        /* HORIZONTAL */
        m_horizontalWidget = new QWidget(this);
        m_horizontalLayout = new QHBoxLayout(m_horizontalWidget);
        m_horizontalLayout->setContentsMargins(1,0,1,0);
        m_horizontalLayout->setSpacing(0);

        /* VERTICAL */
        m_verticalWidget = new QWidget(this);
        m_verticalLayout = new QVBoxLayout(m_verticalWidget);
        m_verticalLayout->setContentsMargins(1,0,0,1);
        m_verticalLayout->setSpacing(0);
        m_verticalWidget->setLayout(m_verticalLayout);
        m_verticalLayout->addWidget(m_horizontalWidget);

        /* BOTTOM */
        iniBottomBar();

        /* LEFT */
        m_leftWidget = new QWidget(m_horizontalWidget);
        m_leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_leftWidget->setFixedWidth(m_sideWidgetWidth);
        m_leftWidget->setObjectName("LeftB");
        m_leftWidget->setStyleSheet("#LeftB {"
                                 "border-top: 1px solid #545454;"
                                 "border-left: 1px solid #545454;"
                                 "border-right: 1px solid #545454;"
                                 "border-bottom: none; margin: "
                                 "0px; padding: 0px;"
                                 "}");
        m_horizontalLayout->addWidget(m_leftWidget, 0, Qt::AlignBottom);

        /* TAB WIDGET */
        m_tabWidget = new WSTabWidget(m_horizontalWidget);
        GlobalMediator::instance()->setWSTabWidget(m_tabWidget);
        m_horizontalLayout->addWidget(m_tabWidget, 0);

        /* RIGHT */
        iniRightBar();

        /* FINALIZE */
        setCentralWidget(m_verticalWidget);



        connect(
                this, &MainWindow::resized, this, &MainWindow::setSidebarHeight);

        connect(
                m_rightToolBar, &RightToolBar::sendButtonClick, m_tabWidget,
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
        btmContent->setStyleSheet("#Outer { border:1px solid #545454; margin: "
                                  "0px; padding: 0px;"
                                  "}");
        m_verticalLayout->addWidget(btmContent);
        btmContent->setFixedHeight(bottomWidgetHeight);
        GlobalMediator::instance()->setBottomToolBar(m_bottomToolBar);
    }

    void MainWindow::iniRightBar()
    {
        rtContent = new QWidget(m_horizontalWidget);
        auto* rtLayout = new QVBoxLayout(rtContent);
        rtLayout->setContentsMargins(5,5,5,5);
        rtContent->setLayout(rtLayout);
        rtContent->setObjectName("RightB");
        rtContent->setStyleSheet("#RightB {"
                                 "border-top: 1px solid #545454;"
                                 "border-left: 1px solid #545454;"
                                 "border-right: 1px solid #545454;"
                                 "border-bottom: none; margin: "
                                 "0px; padding: 0px;"
         "}");
        m_rightToolBar = new RightToolBar(rtContent);
        m_rightToolBar->setFixedWidth(m_sideWidgetWidth);
        rtLayout->addWidget(m_rightToolBar);
        m_horizontalLayout->addWidget(rtContent, 0, Qt::AlignBottom);
    }


    void MainWindow::setSidebarHeight()
    {

        int tabHeight = m_tabWidget->tabBar()->size().height();
        if (tabHeight)
        {
            rtContent->setFixedHeight(m_tabWidget->height() - tabHeight);
            m_leftWidget->setFixedHeight(m_tabWidget->height() - tabHeight);
            /* FIX THIS  */ //// (4/19/23) TODO: fix this tmp fix
            m_leftWidget->setFixedWidth(rtContent->width());
        }
    }

    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            if (event->modifiers() & Qt::ShiftModifier) {
                if (m_tabWidget->getCurrentWorkspace()->getinputBox()) {
                    m_tabWidget->getCurrentWorkspace()->getinputBox()->setFocus();
                }
            }
        } else {
            QMainWindow::keyPressEvent(event);
        }
    }
} // Uik