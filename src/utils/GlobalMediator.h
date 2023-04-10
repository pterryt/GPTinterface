#ifndef GPTINTERFACE_GLOBALMEDIATOR_H
#define GPTINTERFACE_GLOBALMEDIATOR_H

#include <QObject>

class Workspace;
class MainWindow;

class GlobalMediator : public QObject
{
Q_OBJECT

public:
    explicit GlobalMediator(QObject *parent = nullptr);

    ~GlobalMediator() override;
private:


};

#endif // GPTINTERFACE_GLOBALMEDIATOR_H
