#define QT_NO_KEYWORDS
#include "gui/MainWindow.h"

#include <QApplication>

#include <fstream>
#include "utils/GlobalMediator.h"
#include "devtools/ToolTipEventFilter.h"
#include "devtools/logger.h"

/* Add tooltips - to all objects in the gui - that display class, parent class,
 * and grandparent class. */
void installFiltersRecursively(QWidget *widget, ToolTipEventFilter *filter) {
    widget->installEventFilter(filter);
    for (auto child : widget->findChildren<QWidget *>()) {
        installFiltersRecursively(child, filter);
    }
}

int main(int argc, char *argv[])
{
    bool debugMode = true;

    /* Create the logger and set logging level. */
    giLog::initLogger();

    GlobalMediator::create();
    QApplication App(argc, argv);
    Ui::MainWindow mainWindow;


    Aws::SDKOptions options;
    Aws::InitAPI(options);

    if (debugMode)
    {
        ToolTipEventFilter *eventFilter = new ToolTipEventFilter(&mainWindow);
        installFiltersRecursively(&mainWindow, eventFilter);
    }

    mainWindow.show();
    int ret = App.exec();

    delete GlobalMediator::instance();
    Aws::ShutdownAPI(options);
    return ret;
}
