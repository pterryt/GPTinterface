#ifndef GPTINTERFACE_GLOBALMEDIATOR_H
#define GPTINTERFACE_GLOBALMEDIATOR_H

#include <QObject>

class Workspace;
class MainWindow;
class InputBox;
class OutputContainer;
class RightToolBar;

class GlobalMediator : public QObject
{
Q_OBJECT

public:
    static GlobalMediator& instance();
    GlobalMediator(const GlobalMediator &) = delete;
    GlobalMediator& operator=(const GlobalMediator &) = delete;

    int getActiveTabIndex() const;
    void setActiveTabIndex(int index);

public slots:

private:
    explicit GlobalMediator(QObject *parent = nullptr);


    int m_currentTab;


};

#endif // GPTINTERFACE_GLOBALMEDIATOR_H
