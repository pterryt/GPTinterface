#ifndef GPTINTERFACE_OUTPUTCONTAINER_H
#define GPTINTERFACE_OUTPUTCONTAINER_H

#include <QListWidget>

class OutputContainer : public QListWidget
{
Q_OBJECT

public:
    explicit OutputContainer(QWidget *parent = nullptr);

};

#endif // GPTINTERFACE_OUTPUTCONTAINER_H
