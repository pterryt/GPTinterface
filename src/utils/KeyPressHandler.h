#ifndef GPTINTERFACE_KEYPRESSHANDLER_H
#define GPTINTERFACE_KEYPRESSHANDLER_H

#include <QObject>
#include "../gui/Workspace.h"
#include "../gui/widgets/"

class KeyPressHandler : public QObject
{
Q_OBJECT

public:
    explicit KeyPressHandler(QObject *parent = nullptr);
};

#endif // GPTINTERFACE_KEYPRESSHANDLER_H
