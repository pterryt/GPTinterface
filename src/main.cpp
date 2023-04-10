#include <QApplication>

#include "gui/MainWindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    Ui::MainWindow mainWindow;
//    Ui::MainWindow *main_window = new Ui::MainWindow;

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
//    main_window->setPalette(darkPalette);
    QApplication::setPalette(darkPalette);
    App.setStyleSheet("QEditLine, QTextEdit { font-size: 22px; }");


    //show window
//    main_window->show();
    mainWindow.show();
//    int ret = a.exec();

//    delete main_window;

//    return ret;
    return App.exec();
}
