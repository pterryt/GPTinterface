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

#include "widgets/customTextEdit.h"
#include "widgets/customScrollArea.h"
#include "widgets/InputBox.h"
#include "../utils/RequestHandler.h"

class Workspace : public QWidget
{
Q_OBJECT

public:

    explicit Workspace(QWidget *parent = nullptr);
    int getTotalTokens();
    int getInputTokens();


public Q_SLOTS:

    void handleSendButtonClicked();

Q_SIGNALS:
    void sendByKeybind();

private:

    bool m_processingReponse;
    QFutureWatcher<std::string> apiResponseWatcher;
    QPointer<customScrollArea> m_scrollArea;
    QPointer<InputBox> m_inputBox;
    QPointer<QWidget> m_spacer;
    QPointer<QTabWidget> m_tBar;
    QPointer<customTextEdit> m_currentTextEdit;
    QPointer<RequestHandler> requestHandler;
    QFont m_font{"JetBrains Mono", 16};
    int m_inputTokens = 0;
    int m_totalTokens = 0;


    void formatUserInput(customTextEdit* item);
    void formatResponse(customTextEdit* item);


private Q_SLOTS:
    void onNewDataReceived(const QString& data);
    void onTokenCountUpdated(int inputCount, int totalCount);

};


#endif //GPTINTERFACE_WORKSPACE_H
