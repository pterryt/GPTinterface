#define QT_NO_KEYWORDS
#include <QApplication>


#include "gui/MainWindow.h"
#include "devtools/ToolTipEventFilter.h"

void installFiltersRecursively(QWidget *widget, ToolTipEventFilter *filter) {
    widget->installEventFilter(filter);
    for (auto child : widget->findChildren<QWidget *>()) {
        installFiltersRecursively(child, filter);
    }
}

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    Ui::MainWindow mainWindow;

    // dark theme
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
    App.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; "
                      "border: 1px solid black; font-size: 22px}");

    /* Add toolips to all objects recursively */
    ToolTipEventFilter *eventFilter = new ToolTipEventFilter(&mainWindow);
    installFiltersRecursively(&mainWindow, eventFilter);

    mainWindow.show();
    return App.exec();
}
