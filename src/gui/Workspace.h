#ifndef GPTINTERFACE_WORKSPACE_H
#define GPTINTERFACE_WORKSPACE_H

#include "../utils/TikTokenEncoder.h"

#define QT_NO_KEYWORDS
#include <QWidget>
#include <QPointer>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>
#include <QFutureWatcher>

#include "../utils/MediaQueue.h"
#include "widgets/textboxes/customTextEdit.h"
#include "widgets/customScrollArea.h"
#include "widgets/InputBox.h"
#include "../utils/RequestHandler.h"
#include "../utils/PollyUtility.h"

/**
* Holds output box, input box, and a spacer. Generated on a per tab basis.
*/
class Workspace : public QWidget
{
    Q_OBJECT

public:

    explicit Workspace(int number, QWidget *parent = nullptr);

    /**
    * Retrieve the child InputBox.
    * @note Used to reduce the signal/slot chain for focus keybind.
    * Possibly bad practice?
    */
    InputBox *getinputBox();
    /**
    * @return The calculated token count for what is currently in the InputBox.
    */
    int getInputCount() const;
    /**
    * @return The calculated token count for the sum context of the
     * conversation.
    */
    int getContextCount() const;
    /**
    * Builds a conversation from file.
    */
    void rebuildHistoricConversation(QPointer<HistoryButton> &button);

    const QString &getName() const;

    void setName(const QString &name);

    int getNumber() const;

    const QPointer<customScrollArea> &getMScrollArea() const;

    RequestHandler *getRequestHandler();

public Q_SLOTS:

    /**
    * Creates two customTextEdits (for input and output) and adds them to the
    * custom customScrollArea. Also clears the input box and appends it to the
    * first.
    */
    void handleSendButtonClicked();

    void handleContextClearedButtonClicked();

    /* Calculates the number of tokens in the input box and emits a single to
     * update the bottom bar display. */
    void handleInputChanged();

    /**
    * Receives a token count from the RequestHandler, stores it for any
     * future tab switching, and sends it on to the
     * BottomToolBar for display.
    */
    void handleContextTokensCalculated(int count);

Q_SIGNALS:
    /**
     * Signal sent to BottomToolBar when switching tabs.
     * @param count : Calculated token count of current context for this
     * workspace.
    */
    void sendContextTokens(int count);
    void sendNameSet(const QString &name);

private:

    /* Don't start appending to textEdit before TTS has begun. */
    bool firstPass = true;
    /* Returns true if tts mode is on. */
    bool m_ttsMode = false;
    /* Holds text bettween pauses when in TTS mode.*/
    QString bufferString;
    /* Returns true if currently processing an API request. */
    bool m_processingReponse;
    /* Returns true if currently appending text to a codeBlock. */
    bool m_inCodeBlock = false;
    /* Keeps track of the current token count of input text. */
    int m_inputCount = 0;
    /* Keeps track of the current token count of the context container. */
    int m_ContextCount = 0;
    /* Pointer to the customScrollArea. */
    QPointer<customScrollArea> m_scrollArea;

private:
    QPointer<InputBox> m_inputBox;
    QPointer<QWidget> m_spacer;
    QPointer<customTextEdit> m_currentTextEdit;
    QPointer<customTextEdit> m_currentInput;
    QPointer<RequestHandler> requestHandler;
    // (4/25/23) TODO: Should probably be shared.
    QPointer<TikTokenEncoder> encoder;
    /* Class used for synthesizing speech. */
    PollyUtility polly;
    /* Sentence index and corresonding audio clip. */
    int audioClipIndex = 0;
    /* The name of this workspace, determined by tab text. */
    QString Name;
    /* The number of this workspace, used for filing. */
    int Number;

private Q_SLOTS:
    /**
     * Slot that takes data from the SSE, appends it to the current
     * customtextEdit, and updates its sizeHint.
     * @param data : QString data received from the RequestHandler-
     * generally ranging from a few characters to a single word.
     * */
    void onNewDataReceived(const QString& data);

    /**
    * This function flushes the buffer and requests the speech from the
     * remaining text.
    */
    void flushBuffer();

    /**
    * Flush buffer and reenable send.
    */
    void handleResponseFinished();

};


#endif //GPTINTERFACE_WORKSPACE_H
