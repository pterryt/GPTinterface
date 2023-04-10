#ifndef GPTINTERFACE_WORKSPACE_H
#define GPTINTERFACE_WORKSPACE_H

#include <QWidget>
#include <QPointer>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>

class Workspace : public QWidget
{
Q_OBJECT

public:
    explicit Workspace(QWidget *parent = nullptr);

private:
    QPointer<QTextEdit> m_outputBox;
    QPointer<QLineEdit> m_inputBox;
    QPointer<QWidget> m_spacer;
    QPointer<QTabWidget> m_tBar;
};


#endif //GPTINTERFACE_WORKSPACE_H
