#include "Workspace.h"
#include <QVBoxLayout>
#include <iostream>
#include "../utils/RequestHandler.h"
#include <QListWidget>
#include <QtConcurrent/QtConcurrent>


Workspace::Workspace(QWidget *parent) : QWidget(parent)
{
    requestHandler = new RequestHandler(this);
    m_processingReponse = false;
    auto *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setSpacing(10);
    m_outputBox = new OutputContainer;
    m_spacer = new QWidget;
    m_inputBox = new InputBox;
    m_inputBox->setFont(m_font);


    mainLayout->addWidget(m_outputBox);
    mainLayout->addWidget(m_spacer);
    mainLayout->addWidget(m_inputBox);

    connect(requestHandler, &RequestHandler::newDataReceived, this,
            &Workspace::onNewDataReceived);

}
void Workspace::onNewDataReceived(const QString &data)
{
    if (m_currentItem)
    {
        m_currentItem->setText(m_currentItem->text() + data);
    }
}
void Workspace::handleSendButtonClicked()
{
    QString inputString = m_inputBox->toPlainText();
    auto* input = new QListWidgetItem(inputString);
    formatUserInput(input);
    m_outputBox->addItem(input);
    m_inputBox->setText("");

    m_currentItem = new QListWidgetItem("GPT Response: ");
    formatResponse(m_currentItem);
    m_outputBox->addItem(m_currentItem);

    requestHandler->startStreaming(inputString.toStdString());
}


void Workspace::formatUserInput(QListWidgetItem *item)
{
    item->setFont(m_font);
    QString userPrefix = "You said: ";
    item->setText(userPrefix + item->text());
}

void Workspace::formatResponse(QListWidgetItem *item)
{
    item->setFont(m_font);
    QString userPrefix = "GPT Reponse: ";
    item->setText(userPrefix + item->text());
}


