#include "Workspace.h"
#include <QVBoxLayout>


Workspace::Workspace(QWidget *parent) : QWidget(parent)
{
    QFont jbFont("JetBrains Mono");
    auto *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setSpacing(10);
    m_outputBox = new QTextEdit;
    m_outputBox->setFont(jbFont);
    m_spacer = new QWidget;
    m_inputBox = new QLineEdit;
    m_inputBox->setFont(jbFont);
    mainLayout->addWidget(m_outputBox);
    mainLayout->addWidget(m_spacer);
    mainLayout->addWidget(m_inputBox);
}

