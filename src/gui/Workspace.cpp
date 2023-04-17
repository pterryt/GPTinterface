#include "Workspace.h"
#include <QVBoxLayout>
#include <iostream>
#include <QListWidget>
#include <QtConcurrent/QtConcurrent>
#include <QShortcut>

Workspace::Workspace(QWidget *parent) : QWidget(parent)
{
    requestHandler = new RequestHandler(this);
    m_processingReponse = false;
    auto *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    m_scrollArea = new customScrollArea(this);
    m_spacer = new QWidget(this);
    m_inputBox = new InputBox(this);
    m_inputBox->setFont(m_font);


    mainLayout->addWidget(m_scrollArea);
    mainLayout->addWidget(m_spacer);
    mainLayout->addWidget(m_inputBox);


    connect(requestHandler, &RequestHandler::updateTokenDisplay, this, &Workspace::onTokenCountUpdated);

    connect(m_inputBox, &InputBox::enterKeyPressed, this, &Workspace::handleSendButtonClicked);

    connect(requestHandler, &RequestHandler::newDataReceived, this,
            &Workspace::onNewDataReceived);

    connect(requestHandler, &RequestHandler::responseFinshed, this, [this]()
    -> void {m_processingReponse = false;});

}

/**
 * This function takes data from the SSE and appends it to the current
 * customtextEdit and updates its sizeHint
 * */
void Workspace::onNewDataReceived(const QString &data)
{
    if (m_currentTextEdit)
    {
//            qDebug() << "Appending text to CustomTextItem";
            m_currentTextEdit->appendText(data);
            m_currentTextEdit->updateSizeHint();
    }
}

void Workspace::handleSendButtonClicked()
{
    if (!m_processingReponse)
    {
        QString inputString = m_inputBox->toPlainText();
        auto *input = new customTextEdit(inputString);
        input->setTextBackgroundColor(QColor("lightblue"));
        m_scrollArea->addCustomWidget(input);
        input->updateSizeHint();

        m_inputBox->setText("");

        m_currentTextEdit = new customTextEdit("");
        m_scrollArea->addCustomWidget(m_currentTextEdit);
        m_currentTextEdit->updateSizeHint();

        m_processingReponse = true;
        requestHandler->startStreaming(inputString);
    }
}

void Workspace::onTokenCountUpdated(const int inputCount, const int totalCount)
{
    m_inputTokens = inputCount;
    m_totalTokens = totalCount;
}

int Workspace::getInputTokens()
{
    return m_inputTokens;
}


int Workspace::getTotalTokens()
{
    return m_totalTokens;
}


