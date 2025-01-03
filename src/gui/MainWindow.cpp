#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QTabBar>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QFileInfo>
#include <QDir>
#include <QScrollBar>

#include "../utils/GlobalMediator.h"
#include "widgets/RightToolBar.h"
#include "widgets/BottomToolBar.h"
#include "../devtools/logger.h"
#include "widgets/HistoryList.h"
#include "widgets/static_context/scScrollArea.h"
#include "widgets/static_context/scBottomBar.h"

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
        m_horizontalLayout->setContentsMargins(1, 0, 1, 0);
        m_horizontalLayout->setSpacing(0);

        /* VERTICAL */
        m_verticalWidget = new QWidget(this);
        m_verticalLayout = new QVBoxLayout(m_verticalWidget);
        m_verticalLayout->setContentsMargins(1, 0, 0, 1);
        m_verticalLayout->setSpacing(0);
        m_verticalWidget->setLayout(m_verticalLayout);
        m_verticalLayout->addWidget(m_horizontalWidget);


        /* BOTTOM */
        iniBottomBar();

        /* LEFT */
        iniLeftBar();

        m_historyHolder = new QWidget(this);
        m_historyHolder->setFixedWidth(400);
        auto* vl = new QVBoxLayout(m_historyHolder);
        m_historyList = new HistoryList(m_historyHolder);
        vl->addWidget(m_historyList);
        m_historyHolder->setLayout(vl);
        m_historyHolder->hide();
        m_horizontalLayout->addWidget(m_historyHolder);

        /* TAB WIDGET */
        m_tabWidget = new WSTabWidget(m_horizontalWidget);
        GlobalMediator::instance()->setWSTabWidget(m_tabWidget);
        m_horizontalLayout->addWidget(m_tabWidget, 0);

        /* RIGHT */
        iniRightBar();

        /* STATIC CONTEXT MENU */
        iniStaticContextMenu();

        /* FINALIZE */

        setCentralWidget(m_verticalWidget);
        iniTheme();
//        m_staticContextMenu->hide();

        registerCurrentWorkspace(); // (4/20/23) TODO: should be automatic..
        /* CONNNECTIONS */
        connect(
                m_rightToolBar, &RightToolBar::sendButtonClick, m_tabWidget,
                &WSTabWidget::handleSendButtonClicked);

        connect(
                m_rightToolBar, &RightToolBar::clearContextButtonClick, m_tabWidget,
                &WSTabWidget::handleClearContextButtonClicked);

        connect(
                m_tabWidget, &WSTabWidget::sendTokenCounts, m_bottomToolBar,
                &BottomToolBar::handleTabChanged);

        connect(
                GlobalMediator::instance(), &GlobalMediator::sendInputTokenCount,
                m_bottomToolBar, &BottomToolBar::setInputTokens);

        connect(
                m_tabWidget, &WSTabWidget::sendCurrentWorkspaceChanged, this,
                &MainWindow::registerCurrentWorkspace);
        connect(
                m_leftToolBar, &LeftToolBar::sendHistoryButtonClicked,
                this, &MainWindow::handleHistoryButtonClicked);

        connect(
                this, &MainWindow::destroyed, this, []() { QApplication::quit(); }
        );
        connect(
                GlobalMediator::instance(), &GlobalMediator::sendStaticContextMenuButtonClicked,
                this, &MainWindow::toggleStaticContextMenu
                );
        connect(
                GlobalMediator::instance(), &GlobalMediator::sendSCToggled, this, &MainWindow::handleSCToggled
                );
        connect(
                GlobalMediator::instance(), &GlobalMediator::sendSCComboBoxChanged, this, &MainWindow::handleSCComboBoxChanged
        );
    }

    MainWindow::~MainWindow()
    {
        delete ui;
        cleanUpFolders("audio_clips");
    }

    void MainWindow::iniBottomBar()
    {
        /* Without a parent widget, outlining the bottom bar directly is not
         * visible. */
        /* Create Widgets */
        auto *btmContent = new QWidget(m_verticalWidget);
        auto *btmLayout = new QHBoxLayout(btmContent);
        m_bottomToolBar = new BottomToolBar(btmContent);

        /* Arrange Widgets */
        m_verticalLayout->addWidget(btmContent);
        btmLayout->addWidget(m_bottomToolBar);
        btmContent->setLayout(btmLayout);

        /* Styling */
        btmLayout->setContentsMargins(0, 0, 0, 0);
        btmContent->setFixedHeight(m_screen->size().height() * .04);
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
        auto *rightLayout = new QVBoxLayout(rightContent);
        m_rightToolBar = new RightToolBar(rightContent);

        /* Arrange Widgets */
        rightContent->setLayout(rightLayout);
        rightLayout->addWidget(m_rightToolBar);
        m_horizontalLayout->addWidget(rightContent, 0, Qt::AlignBottom);

        /* Styling */
        m_rightToolBar->setFixedWidth(m_sideWidgetWidth);
        rightLayout->setContentsMargins(5, 5, 5, 5);
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
        auto *leftLayout = new QVBoxLayout(leftContent);
        m_leftToolBar = new LeftToolBar(leftContent);

        /* Arrange Widgets */
        leftContent->setLayout(leftLayout);
        leftLayout->addWidget(m_leftToolBar);
        m_horizontalLayout->addWidget(leftContent, 0, Qt::AlignBottom);

        /* Styling */
        m_leftToolBar->setFixedWidth(m_sideWidgetWidth);
        leftLayout->setContentsMargins(5, 5, 5, 5);
        /* All children are outlined if you don't style as object. */
        leftContent->setObjectName("LeftB");
        leftContent->setStyleSheet("#LeftB {"
                                   "border-top: 1px solid #545454;"
                                   "border-left: 1px solid #545454;"
                                   "border-right: 1px solid #545454;"
                                   "border-bottom: none;"
                                   "}");

        GlobalMediator::instance()->setLeftToolBar(m_leftToolBar);
    }

    void MainWindow::setSidebarHeight()
    {

        int tabHeight = m_tabWidget->tabBar()->size().height();
        int newHeight = m_tabWidget->height() - tabHeight;
        if (tabHeight)
        {
            rightContent->setFixedHeight(newHeight);
            leftContent->setFixedHeight(newHeight);
            m_historyHolder->setFixedHeight(newHeight);
        }
    }

    /* ------------------- -------- ------------------- */
    /* ------------------- KEYBINDS ------------------- */
    /* ------------------- -------- ------------------- */

    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        /* Shift + Enter -> focus the inputBox. */
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                if (m_tabWidget->getCurrentWorkspace()->getinputBox())
                {
                    m_tabWidget->getCurrentWorkspace()->getinputBox()->setFocus();
                }
            }
        }
        else if (event->key() == Qt::Key_U)
        {
            if (event->modifiers() & Qt::ControlModifier)
            {
                m_currentWorkspace->getMScrollArea()->verticalScrollBar()->setValue(m_currentWorkspace->getMScrollArea()->verticalScrollBar()->value() - 500);
            }
        }
        else if (event->key() == Qt::Key_D)
        {
            if (event->modifiers() & Qt::ControlModifier)
            {
                m_currentWorkspace->getMScrollArea()->verticalScrollBar()->setValue(m_currentWorkspace->getMScrollArea()->verticalScrollBar()->value() + 500);
            }
        }
        else if (event->key() == Qt::Key_H)
        {
            handleHistoryButtonClicked();
        }
        else if (event->key() == Qt::Key_C)
        {
            toggleStaticContextMenu();
        }
        else if (event->key() == Qt::Key_K)
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                m_tabWidget->handleMoveRight();
            }
            else
            {
                m_currentWorkspace->getMScrollArea()->verticalScrollBar()->setValue(m_currentWorkspace->getMScrollArea()->verticalScrollBar()->value() - 200);
            }
        }
        else if (event->key() == Qt::Key_J)
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                m_tabWidget->handleMoveLeft();
            }
            else
            {
                m_currentWorkspace->getMScrollArea()->verticalScrollBar()->setValue(m_currentWorkspace->getMScrollArea()->verticalScrollBar()->value() + 200);
            }
        }
        else if (event->key() == Qt::Key_X)
        {
            m_tabWidget->handleCloseTab(m_tabWidget->currentIndex());
        }
        else if (event->key() == Qt::Key_T)
        {
            m_tabWidget->newTab();
        }
        else if (event->key() == Qt::Key_0)
        {
            m_currentWorkspace->handleContextClearedButtonClicked();
        }
        else
        {
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
        m_scScroll->loadStaticContexts(m_currentWorkspace->getRequestHandler()->scSettings);
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
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
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
        centerStaticContextMenu();
    }


    void MainWindow::on_actionExit_triggered()
    {
        QApplication::quit();
    }

    void MainWindow::cleanUpFolders(const QString& path)
    {
        QDir dir(path);
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        for (const QFileInfo& fileInfo : dir.entryInfoList()) {
            if (fileInfo.isDir()) {
                cleanUpFolders(fileInfo.absoluteFilePath());
                dir.rmdir(fileInfo.absoluteFilePath());
            } else {
                dir.remove(fileInfo.absoluteFilePath());
            }
        }
    }

    void MainWindow::handleHistoryButtonClicked()
    {
        if (m_historyHolder->isHidden())
        {
            m_historyHolder->show();
//            m_historyList->setFocus();
        }
        else
        {
            m_historyHolder->hide();
        }
    }

    void MainWindow::iniStaticContextMenu()
    {
        m_staticContextMenu = new QWidget(this);
        m_staticContextMenu->hide();
        m_staticContextMenu->setContentsMargins(0,0,0,0);

        m_staticContextMenu->setFixedWidth(1000);
        m_staticContextMenu->setFixedHeight(500);

        auto* layout = new QVBoxLayout(m_staticContextMenu);
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);
        m_scScroll = new scScrollArea(m_staticContextMenu);
        auto* scBar = new scBottomBar(m_staticContextMenu);
        scBar->setStyleSheet("background:#252525;");
        m_staticContextMenu->setStyleSheet("background:#535353;");
        layout->addWidget(m_scScroll);
        layout->addWidget(scBar);
        m_staticContextMenu->setLayout(layout);
    }

    void MainWindow::toggleStaticContextMenu()
    {
        if (m_staticContextMenu->isHidden())
        {
            m_staticContextMenu->show();
        }
        else
        {
            m_staticContextMenu->hide();
            QHash<QUuid, scItem*>::iterator it;
            for (it = m_scScroll->getscUOMap()->begin(); it != m_scScroll->getscUOMap()->end(); ++it)
            {
                it.value()->setTextLocked();
            }
        }
    }

    void MainWindow::centerStaticContextMenu()
    {
        // (5/18/23) TODO: hardcoded values, figure out dynamic center screen
        QRect sGeo = m_screen->geometry();
        int x = (sGeo.width() - m_staticContextMenu->width() - 160);
        int y = (sGeo.height() - m_staticContextMenu->height() - 125);
        m_staticContextMenu->move(x, y);

    }

    void MainWindow::handleSCToggled(QUuid uid, int enabled)
    {
        if(enabled == 2)
        {
            m_currentWorkspace->getRequestHandler()->scSettings->insert(uid, 0);
        }
        else
        {
            m_currentWorkspace->getRequestHandler()->scSettings->remove(uid);
        }
    }

    void MainWindow::handleSCComboBoxChanged(QUuid uid, int index)
    {
        m_currentWorkspace->getRequestHandler()->scSettings->insert(uid, index);
    }

} // Ui
