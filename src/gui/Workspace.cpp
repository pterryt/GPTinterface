#include "Workspace.h"

#include <QVBoxLayout>
#include <QtConcurrent/QtConcurrent>
#include <QShortcut>
#include <QTextBlock>
#include <QScrollBar>

#include "../utils/GlobalMediator.h"
#include "widgets/textboxes/codeBlock.h"
#include "widgets/textboxes/userText.h"
#include "widgets/textboxes/aiText.h"
#include "widgets/WSTabWidget.h"
#include "widgets/BottomToolBar.h"
#include <thread>


Workspace::Workspace(const int number, QWidget *parent) : QWidget(parent), Number(number)
{
    /* Needed for calculating tokens from the InputBox on the fly. */
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

    QString dirname =
            "audio_clips/ws_" + QString::number(Number);
    QDir dir;

    if (!dir.exists(dirname))
    {
        dir.mkdir(dirname);
    }


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

    // (5/5/23) TODO: consider instead passing the textEdits to workspace for caching
    connect(
            this, &Workspace::sendNameSet, m_scrollArea, &customScrollArea::handleSetWSName
            );
}


void Workspace::onNewDataReceived(const QString &data)
{
//    qDebug() << data;
    if (m_ttsMode && !m_inCodeBlock)
    {
        bufferString.append(data);
//        if (bufferString.length() >= 75)
        if (bufferString.contains(QChar('.')) || bufferString.contains
        (QString("。")))
        {
            flushBuffer();
        }
    }
    if (m_currentTextEdit)
    {
        /* Append the text first in case of split code block markers '''. */
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
                    m_currentTextEdit = new codeBlock(Number, m_scrollArea);
                    m_scrollArea->addCustomWidget(m_currentTextEdit);
                    m_scrollArea->updateScrollPosition();
                    QCoreApplication::processEvents();
                    m_inCodeBlock = true;
                }
                /* Otherwise create an aiText and add it to the scrollArea. */
                else
                {
                    m_currentTextEdit = new aiText(Number, m_scrollArea);
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

        if (Name == "")
        {
            setName(inputString);
        }
        m_currentInput = new userText(Number, m_scrollArea);
        m_scrollArea->addCustomWidget(m_currentInput);
        m_scrollArea->updateScrollPosition();
        QCoreApplication::processEvents();

        m_currentInput->appendText(inputString);
        m_scrollArea->updateScrollPosition();
        QCoreApplication::processEvents();

        m_currentTextEdit = new aiText(Number, m_scrollArea);
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
    m_inputCount = TikTokenEncoder::encode(
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
    std::thread thread(&PollyUtility::synthesizeSpeech, &polly, Number, m_currentTextEdit->convoIndex,
                       audioClipIndex, bufferString);
    thread.detach();
    bufferString = "";
    audioClipIndex ++;
}

void Workspace::handleResponseFinished()
{
    m_processingReponse = false;
    if (!bufferString.isEmpty())
    {
        flushBuffer();
    }
}

const QString &Workspace::getName() const
{
    return Name;
}

void Workspace::setName(const QString &name)
{
    Name = name.left(35);
    Q_EMIT sendNameSet(Name);
}

int Workspace::getNumber() const
{
    return Number;
}

void Workspace::handleContextClearedButtonClicked()
{
    requestHandler->clearContext();
}

void Workspace::rebuildHistoricConversation(QPointer<HistoryButton> &button)
{
    hide();
    QFile hFile = QFile(button->getMFile());
    hFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument jDoc = QJsonDocument::fromJson(hFile.readAll());
    QJsonArray arr = jDoc.array();
    setName(arr[0].toObject()["name"].toString());

    for (int i = 1; i < arr.size(); i++)
    {
        QJsonObject obj = arr[i].toObject();

        int eType = obj["type"].toInteger();
        customTextEdit* cte;
        switch(eType)
        {
            case 0:
                cte = new userText(i-1, m_scrollArea);
                break;
            case 1:
                cte = new aiText(i-1, m_scrollArea);
                break;
            case 2:
                cte = new codeBlock(i-1, m_scrollArea);
                break;
        }

        cte->appendText(obj["text"].toString());
        m_scrollArea->addCustomWidget(cte);
        m_scrollArea->hasChanged = false;
        m_scrollArea->isHistoric = true;
        m_scrollArea->hButton = button;
    }
    show();
}

const QPointer<customScrollArea> &Workspace::getMScrollArea() const
{
    return m_scrollArea;
}

RequestHandler *Workspace::getRequestHandler()
{
    return requestHandler;
}
