#ifndef GPTINTERFACE_WORKSPACE_H
#define GPTINTERFACE_WORKSPACE_H

#include <QWidget>
#include <QPointer>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>
#include <QListWidget>
#include "widgets/OutputContainer.h"
#include "widgets/InputBox.h"

class Workspace : public QWidget
{
Q_OBJECT

public:

    explicit Workspace(QWidget *parent = nullptr);

public slots:

    void handleSendButtonClicked();


private:

    QPointer<OutputContainer> m_outputBox;
    QPointer<InputBox> m_inputBox;
    QPointer<QWidget> m_spacer;
    QPointer<QTabWidget> m_tBar;
};


#endif //GPTINTERFACE_WORKSPACE_H
