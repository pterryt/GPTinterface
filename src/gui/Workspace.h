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

#include "widgets/textboxes/customTextEdit.h"
#include "widgets/customScrollArea.h"
#include "widgets/InputBox.h"
#include "../utils/RequestHandler.h"

class Workspace : public QWidget
{
Q_OBJECT

public:

    explicit Workspace(QWidget *parent = nullptr);

public Q_SLOTS:

    void handleSendButtonClicked();
    void handleInputChanged();

Q_SIGNALS:

    void sendByKeybind();
    void sendInputTokenCount(int count);

private:

    bool m_processingReponse;
    bool m_inCodeBlock = false;
    QFutureWatcher<std::string> apiResponseWatcher;
    QPointer<customScrollArea> m_scrollArea;
    QPointer<InputBox> m_inputBox;
    QPointer<QWidget> m_spacer;
    QPointer<QTabWidget> m_tBar;
    QPointer<customTextEdit> m_currentTextEdit;
    QPointer<RequestHandler> requestHandler;
    QPointer<TikTokenEncoder> encoder;
    QFont m_font{"JetBrains Mono", 16};



private Q_SLOTS:
    void onNewDataReceived(const QString& data);


};


#endif //GPTINTERFACE_WORKSPACE_H
