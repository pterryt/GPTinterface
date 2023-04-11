#include "Workspace.h"
#include <QVBoxLayout>
#include <iostream>


Workspace::Workspace(QWidget *parent) : QWidget(parent)
{
    QFont jbFont("JetBrains Mono");
    auto *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setSpacing(10);
    m_outputBox = new OutputContainer;
    m_outputBox->setFont(jbFont);
    m_spacer = new QWidget;
    m_inputBox = new InputBox;
    m_inputBox->setFont(jbFont);


    mainLayout->addWidget(m_outputBox);
    mainLayout->addWidget(m_spacer);
    mainLayout->addWidget(m_inputBox);
}

void Workspace::handleSendButtonClicked()
{
    std::cout << "button click acknowledged in ws" << std::endl;
    m_inputBox->setText("");
}


