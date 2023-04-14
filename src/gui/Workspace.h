#ifndef GPTINTERFACE_WORKSPACE_H
#define GPTINTERFACE_WORKSPACE_H

#include <QWidget>
#include <QPointer>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>
#include <QFutureWatcher>

#include "widgets/customTextEdit.h"
#include "widgets/customScrollArea.h"
#include "widgets/OutputContainer.h"
#include "widgets/InputBox.h"
#include "../utils/RequestHandler.h"

class Workspace : public QWidget
{
Q_OBJECT

public:

    explicit Workspace(QWidget *parent = nullptr);

public slots:

    void handleSendButtonClicked();

signals:
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


    void formatUserInput(customTextEdit* item);
    void formatResponse(customTextEdit* item);


private slots:
    void onNewDataReceived(const QString& data);

};


#endif //GPTINTERFACE_WORKSPACE_H
