#ifndef GPTINTERFACE_INPUTMESSAGE_H
#define GPTINTERFACE_INPUTMESSAGE_H

#include <QListWidget>
#include <QListWidgetItem>

class InputMessage : public QListWidgetItem
{
Q_OBJECT

public:
    explicit InputMessage(const QString& text, QListWidget *parent = nullptr);
};

#endif // GPTINTERFACE_INPUTMESSAGE_H
