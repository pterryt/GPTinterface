//
// Created by phil on 4/7/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_workspace.h" resolved

#include "workspace.h"
#include <QVBoxLayout>


workspace::workspace(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    m_inputBox = new QLineEdit;
    m_outputBox = new QTextEdit;
    m_spacer = new QWidget;
    mainLayout->addWidget(m_inputBox);
    mainLayout->addWidget(m_outputBox);
    mainLayout->addWidget(m_spacer);
}

