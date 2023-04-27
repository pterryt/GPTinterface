#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QTabBar>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "../utils/GlobalMediator.h"
#include "widgets/RightToolBar.h"
#include "widgets/BottomToolBar.h"
#include "../devtools/logger.h"


namespace Ui
{
    MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::mainwindow)
    {
        /* INIT DESIGN */
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
        iniLeftBar();

        /* TAB WIDGET */
        m_tabWidget = new WSTabWidget(m_horizontalWidget);
        GlobalMediator::instance()->setWSTabWidget(m_tabWidget);
        m_horizontalLayout->addWidget(m_tabWidget, 0);

        /* RIGHT */
        iniRightBar();

        /* FINALIZE */
        setCentralWidget(m_verticalWidget);
        iniTheme();


        registerCurrentWorkspace(); // (4/20/23) TODO: should be automatic..

        /* CONNNECTIONS */
        connect(
                m_rightToolBar, &RightToolBar::sendButtonClick, m_tabWidget,
                &WSTabWidget::handleSendButtonClicked);

        connect(
                m_tabWidget, &WSTabWidget::sendTokenCounts, m_bottomToolBar,
                &BottomToolBar::handleTabChanged
        );

        connect(
                GlobalMediator::instance(), &GlobalMediator::sendInputTokenCount,
                m_bottomToolBar, &BottomToolBar::setInputTokens
        );

        connect(m_tabWidget, &WSTabWidget::sendCurrentWorkspaceChanged, this,
                &MainWindow::registerCurrentWorkspace);


    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::iniBottomBar()
    {
        /* Without a parent widget, outlining the bottom bar directly is not
         * visible. */
        /* Create Widgets */
        auto* btmContent = new QWidget(m_verticalWidget);
        auto* btmLayout = new QHBoxLayout(btmContent);
        m_bottomToolBar = new BottomToolBar(btmContent);

        /* Arrange Widgets */
        m_verticalLayout->addWidget(btmContent);
        btmLayout->addWidget(m_bottomToolBar);
        btmContent->setLayout(btmLayout);

        /* Styling */
        btmLayout->setContentsMargins(0,0,0,0);
        btmContent->setFixedHeight(m_screen->size().height()*.04);
        /* All children are outlined if you don't style as object. */
        btmContent->setObjectName("Outer");
        btmContent->setStyleSheet("#Outer { "
                                  "border:1px solid #545454; "
                                  "}");

        GlobalMediator::instance()->setBottomToolBar(m_bottomToolBar);
    }

    void MainWindow::iniRightBar()
    {
        /* Without a parent widget, outlining the bottom bar directly is not
         * visible. */
        /* Create Widgets */
        rightContent = new QWidget(m_horizontalWidget);
        auto* rightLayout = new QVBoxLayout(rightContent);
        m_rightToolBar = new RightToolBar(rightContent);

        /* Arrange Widgets */
        rightContent->setLayout(rightLayout);
        rightLayout->addWidget(m_rightToolBar);
        m_horizontalLayout->addWidget(rightContent, 0, Qt::AlignBottom);

        /* Styling */
        m_rightToolBar->setFixedWidth(m_sideWidgetWidth);
        rightLayout->setContentsMargins(5,5,5,5);
        /* All children are outlined if you don't style as object. */
        rightContent->setObjectName("RightB");
        rightContent->setStyleSheet("#RightB {"
                                    "border-top: 1px solid #545454;"
                                    "border-left: 1px solid #545454;"
                                    "border-right: 1px solid #545454;"
                                    "border-bottom: none;"
                                   "}");
    }

    void MainWindow::iniLeftBar()
    {
        /* Without a parent widget, outlining the bottom bar directly is not
         * visible. */
        /* Create Widgets */
        leftContent = new QWidget(m_horizontalWidget);
        auto* leftLayout = new QVBoxLayout(leftContent);
        m_leftToolBar = new LeftToolBar(leftContent);

        /* Arrange Widgets */
        leftContent->setLayout(leftLayout);
        leftLayout->addWidget(m_leftToolBar);
        m_horizontalLayout->addWidget(leftContent, 0, Qt::AlignBottom);

        /* Styling */
        m_leftToolBar->setFixedWidth(m_sideWidgetWidth);
        leftLayout->setContentsMargins(5,5,5,5);
        /* All children are outlined if you don't style as object. */
        leftContent->setObjectName("LeftB");
        leftContent->setStyleSheet("#LeftB {"
                                     "border-top: 1px solid #545454;"
                                     "border-left: 1px solid #545454;"
                                     "border-right: 1px solid #545454;"
                                     "border-bottom: none;"
                                     "}");


    }

    void MainWindow::setSidebarHeight()
    {

        int tabHeight = m_tabWidget->tabBar()->size().height();
        int newHeight = m_tabWidget->height() - tabHeight;
        if (tabHeight)
        {
            rightContent->setFixedHeight(newHeight);
            leftContent->setFixedHeight(newHeight);
        }
    }

    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        /* Shift + Enter -> focus the inputBox. */
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

    void MainWindow::registerCurrentWorkspace()
    {
        if (m_currentWorkspace)
        {
            unregisterCurrentWorkspace();
        }

        m_currentWorkspace = m_tabWidget->getCurrentWorkspace();

        connect(
                m_currentWorkspace, &Workspace::sendContextTokens,
                m_bottomToolBar,
                &BottomToolBar::setContextTokens
                );
    }

    void MainWindow::unregisterCurrentWorkspace()
    {
        disconnect(
               m_currentWorkspace, &Workspace::sendContextTokens,
               m_bottomToolBar, &BottomToolBar::setContextTokens
                );
    }

    void MainWindow::iniTheme()
    {
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53,53,53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25,25,25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53,53,53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        QApplication::setPalette(darkPalette);

        setStyleSheet("QToolTip { color: #ffffff; background-color: "
                         "#2a82da; "
                          "border: 1px solid black; font-size: 22px}");
    }

    /* Resize the sidebars, which are based on the tabwidget's height. */
    void MainWindow::resizeEvent(QResizeEvent *event)
    {
        QMainWindow::resizeEvent(event);
        setSidebarHeight();
    }

} // Ui