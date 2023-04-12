#include "Workspace.h"
#include <QVBoxLayout>
#include <iostream>
#include "../utils/RequestHandler.h"
#include <QListWidget>
#include <QtConcurrent/QtConcurrent>


Workspace::Workspace(QWidget *parent) : QWidget(parent)
{
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

    connect(&apiResponseWatcher, &QFutureWatcher<std::string>::finished,
            this, &Workspace::handleResponse);
}

void Workspace::handleSendButtonClicked()
{
    if (!m_processingReponse)
    {
        QString inputString = m_inputBox->toPlainText();
        auto* input = new QListWidgetItem(inputString);
        formatUserInput(input);
        m_outputBox->addItem(input);
        m_inputBox->setText("");

        QFuture<std::string> apiResponseFuture = QtConcurrent::run
                (RequestHandler::qPTrequest, inputString.toStdString());

        apiResponseWatcher.setFuture(apiResponseFuture);

        m_processingReponse = true;
    }
}

void Workspace::handleResponse()
{
    std::string response = apiResponseWatcher.future().result();
    m_processingReponse = false;
    auto* input = new QListWidgetItem(QString::fromStdString(response));
    formatResponse(input);
    m_outputBox->addItem(input);
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


