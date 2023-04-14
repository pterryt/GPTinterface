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
    mainLayout->setSpacing(10);
    m_scrollArea = new customScrollArea;
    m_spacer = new QWidget;
    m_inputBox = new InputBox(this);
    m_inputBox->setFont(m_font);


    mainLayout->addWidget(m_scrollArea);
    mainLayout->addWidget(m_spacer);
    mainLayout->addWidget(m_inputBox);

//    auto *sendEnter = new QShortcut(QKeySequence(Qt::Key_Return), this);
//    sendEnter->setContext(Qt::WidgetShortcut);
//
//    connect(sendEnter, &QShortcut::activated, this,
//            &Workspace::handleSendButtonClicked);


    connect(m_inputBox, &InputBox::enterKeyPressed, this, &Workspace::handleSendButtonClicked);

    connect(requestHandler, &RequestHandler::newDataReceived, this,
            &Workspace::onNewDataReceived);

    connect(requestHandler, &RequestHandler::responseFinshed, this, [this]()
    -> void {m_processingReponse = false;});

}




void Workspace::onNewDataReceived(const QString &data)
{
    if (m_currentTextEdit)
    {
            qDebug() << "Appending text to CustomTextItem";
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
//        formatUserInput(input);
        m_scrollArea->addCustomWidget(input);
        m_inputBox->setText("");

        m_currentTextEdit = new customTextEdit("", this);
//        formatResponse(m_currentTextEdit);
        m_scrollArea->addCustomWidget(m_currentTextEdit);
        m_currentTextEdit->updateSizeHint();

        m_processingReponse = true;
        requestHandler->startStreaming(inputString.toStdString());
    }
}


//void Workspace::formatUserInput(customTextEdit *item)
//{
//    item->setFont(m_font);
//    item->updateSizeHint();
//}
//
//void Workspace::formatResponse(customTextEdit *item)
//{
//    item->setFont(m_font);
//}


