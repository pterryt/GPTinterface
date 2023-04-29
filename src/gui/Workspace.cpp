#include "Workspace.h"

#include <QVBoxLayout>
#include <QListWidget>
#include <QtConcurrent/QtConcurrent>
#include <QShortcut>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QScrollBar>
#include <fstream>

#include "../utils/GlobalMediator.h"
#include "widgets/textboxes/codeBlock.h"
#include "widgets/textboxes/userText.h"
#include "widgets/textboxes/aiText.h"
#include "widgets/WSTabWidget.h"
#include "widgets/BottomToolBar.h"
#include "../utils/PollyUtility.h"


Workspace::Workspace(QWidget *parent) : QWidget(parent)
{
    polly.startProcessing();
    /* Needed for calculating tokens from the InputBox on the fly. */
    encoder = new TikTokenEncoder(this);
    requestHandler = new RequestHandler(this);

    /* Used to avoid simultaneous requests from one workspace. */
    m_processingReponse = false;

    auto *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    m_scrollArea = new customScrollArea(this);
    m_spacer = new QWidget(this);
    m_inputBox = new InputBox(this);

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
            &Workspace::handleResponseFinished);

    connect(
            m_inputBox, &InputBox::textChanged, this,
            &Workspace::handleInputChanged);

    connect(
            requestHandler, &RequestHandler::sendContextTokensCalculated, this,
            &Workspace::handleContextTokensCalculated
            );
}

Workspace::~Workspace()
{
}

void Workspace::onNewDataReceived(const QString &data)
{
//    qDebug() << data;
    if (m_ttsMode && !m_inCodeBlock)
    {
        bufferString.append(data);
        if (bufferString.length() >= 75)
        {
            flushBuffer();
        }
    }
    if (m_currentTextEdit)
    {
        /* Append the text first incase of split code block markers '''. */
        m_currentTextEdit->appendText(data);
        m_scrollArea->updateScrollPosition();
        /* Text boxes "bounce" during new line appends without this function
         * call. */
        QCoreApplication::processEvents();

        auto* doc = m_currentTextEdit->document();
        int count = static_cast<int>(data.count(QChar('\n')));

        if (count > 0)
        {
            /* Subtract the number of new line characters to find the last
             * block with text. */
            QTextBlock targetBlock =
                    doc->findBlockByNumber(doc->blockCount() - (1 + count));

            // (4/25/23) TODO: Need something similar for end of response.
            if (targetBlock.text().contains("```"))
            {
                QTextCursor *cursor = m_currentTextEdit->m_appendCursor;
                cursor->setPosition(targetBlock.position());
                cursor->movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
                cursor->removeSelectedText();
                m_currentTextEdit->updateSizeHint();
                m_scrollArea->updateScrollPosition();
                QCoreApplication::processEvents();

                /* If we're not in a code block, create one and add it to the
                 * scrollArea. */
                if (!m_inCodeBlock)
                {
                    m_currentTextEdit->removeTrailingBlankLines();
                    m_currentTextEdit = new codeBlock(m_scrollArea);
                    m_scrollArea->addCustomWidget(m_currentTextEdit);
                    m_scrollArea->updateScrollPosition();
                    QCoreApplication::processEvents();
                    m_inCodeBlock = true;
                }
                /* Otherwise create an aiText and add it to the scrollArea. */
                else
                {
                    m_currentTextEdit = new aiText(m_scrollArea);
                    m_scrollArea->addCustomWidget(m_currentTextEdit);
                    m_scrollArea->updateScrollPosition();
                    QCoreApplication::processEvents();
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

        m_currentInput = new userText(m_scrollArea);
        m_scrollArea->addCustomWidget(m_currentInput);
        m_scrollArea->updateScrollPosition();
        QCoreApplication::processEvents();

        m_currentInput->appendText(inputString);
        m_scrollArea->updateScrollPosition();
        QCoreApplication::processEvents();

        m_currentTextEdit = new aiText(m_scrollArea);
        m_scrollArea->addCustomWidget(m_currentTextEdit);
        m_scrollArea->updateScrollPosition();
        QCoreApplication::processEvents();

        m_processingReponse = true;
        requestHandler->startStreaming(m_inputCount, inputString);
        m_inputBox->setText("");
    }
}

/* Get the token count as the user types. */
void Workspace::handleInputChanged()
{
    m_inputCount = encoder->encode(
            m_inputBox->toPlainText().toStdString());

    Q_EMIT GlobalMediator::instance()->sendInputTokenCount(m_inputCount);
}

void Workspace::handleContextTokensCalculated(int count)
{
   m_ContextCount = count;
   Q_EMIT sendContextTokens(count);
}

InputBox *Workspace::getinputBox()
{
    return m_inputBox;
}

int Workspace::getInputCount() const
{
    return m_inputCount;
}

int Workspace::getContextCount() const
{
    return m_ContextCount;
}

void Workspace::flushBuffer()
{
    polly.addText(bufferString);
    bufferString = "";
}

void Workspace::handleResponseFinished()
{
    m_processingReponse = false;
    if (!bufferString.isEmpty())
    {
        flushBuffer();
    }
}
