#include "Workspace.h"
#include <QVBoxLayout>
#include <iostream>
#include <QListWidget>
#include <QtConcurrent/QtConcurrent>
#include <QShortcut>
#include <QTextBlock>
#include "../utils/GlobalMediator.h"
#include "widgets/textboxes/codeBlock.h"
#include "widgets/textboxes/userText.h"
#include "widgets/textboxes/aiText.h"
#include "widgets/WSTabWidget.h"
#include "widgets/BottomToolBar.h"

Workspace::Workspace(QWidget *parent) : QWidget(parent)
{

    encoder = new TikTokenEncoder(this);
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

    connect(
            m_inputBox, &InputBox::enterKeyPressed, this,
            &Workspace::handleSendButtonClicked);

    connect(
            requestHandler, &RequestHandler::newDataReceived, this,
            &Workspace::onNewDataReceived);

    connect(
            requestHandler, &RequestHandler::responseFinshed, this,
            [this]()-> void {m_processingReponse = false;});

    connect(
            m_inputBox, &InputBox::textChanged, this,
            &Workspace::handleInputChanged);

    connect(
            requestHandler, &RequestHandler::sendTotalTokensCalculated, this,
            &Workspace::handleTotalTokensCalculated
            );

}

/**
 * This function takes data from the SSE, appends it to the current
 * customtextEdit, and updates its sizeHint.
 * */
void Workspace::onNewDataReceived(const QString &data)
{
    if (m_currentTextEdit)
    {
        m_currentTextEdit->appendText(data);
        auto* doc = m_currentTextEdit->document();
        int count = static_cast<int>(data.count(QChar('\n')));

        if (count > 0)
        {
            QTextBlock targetBlock =
                    doc->findBlockByNumber(doc->blockCount() - (1 + count));

            if (targetBlock.text().contains("```"))
            {
                QTextCursor *cursor = m_currentTextEdit->m_appendCursor;
                cursor->setPosition(targetBlock.position());
                cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
                cursor->removeSelectedText();
                m_currentTextEdit->updateSizeHint();

                if (!m_inCodeBlock)
                {
                    m_currentTextEdit->removeTrailingBlankLines();
                    m_currentTextEdit = new codeBlock(m_scrollArea);
                    m_scrollArea->addCustomWidget(m_currentTextEdit);
                    m_inCodeBlock = true;
                }
                else
                {
                    m_currentTextEdit = new aiText(m_scrollArea);
                    m_inCodeBlock = false;
                }
            }
        }
    }
}


void Workspace::handleSendButtonClicked()
{
    if (!m_processingReponse)
    {
        QString inputString = m_inputBox->toPlainText();
        if (inputString == "") return;
        auto *input = new userText(m_scrollArea);
        m_scrollArea->addCustomWidget(input);
        input->appendText(inputString);
        input->removeTrailingBlankLines();

        m_currentTextEdit = new aiText(m_scrollArea);
        m_scrollArea->addCustomWidget(m_currentTextEdit);
        m_currentTextEdit->updateSizeHint();

        m_processingReponse = true;
        requestHandler->startStreaming(m_inputCount, inputString);
        m_inputBox->setText("");
    }
}

/* Calculates the number of tokens in the input box and emits a single to
 * update the bottom bar display. */
void Workspace::handleInputChanged()
{
    m_inputCount = encoder->encode(
            m_inputBox->toPlainText().toStdString());

    Q_EMIT GlobalMediator::instance()->sendInputTokenCount(m_inputCount);
}

void Workspace::handleTotalTokensCalculated(int count)
{
   m_totalCount = count;
   if (GlobalMediator::instance()->getWSTabWidget()->getCurrentWorkspace() ==
   this)
   {
       GlobalMediator::instance()->getBottomToolBar()->setSumContextTokens(count);
   }
}

InputBox *Workspace::getinputBox()
{
    return m_inputBox;
}

