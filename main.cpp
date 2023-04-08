#include <QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ui::mainwindow *main_window = new Ui::mainwindow;
//    main_window->show();
    int ret = a.exec();

    delete main_window;

    return ret;
}
