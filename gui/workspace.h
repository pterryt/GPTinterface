//
// Created by phil on 4/7/23.
//

#ifndef GPTINTERFACE_WORKSPACE_H
#define GPTINTERFACE_WORKSPACE_H

#include <QWidget>
#include <QPointer>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>




class workspace : public QWidget
{
Q_OBJECT

public:
    explicit workspace(QWidget *parent = nullptr);

private:
    QPointer<QTextEdit> m_outputBox;
    QPointer<QLineEdit> m_inputBox;
    QPointer<QWidget> m_spacer;
    QPointer<QTabWidget> m_tBar;
    int b_tabCount;


};


#endif //GPTINTERFACE_WORKSPACE_H
