#ifndef GPTINTERFACE_WORKSPACE_H
#define GPTINTERFACE_WORKSPACE_H

#include <QWidget>
#include <QPointer>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>
#include <QFutureWatcher>
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


private:

    bool m_processingReponse;
    QFutureWatcher<std::string> apiResponseWatcher;
    QPointer<OutputContainer> m_outputBox;
    QPointer<InputBox> m_inputBox;
    QPointer<QWidget> m_spacer;
    QPointer<QTabWidget> m_tBar;
    QListWidgetItem* m_currentItem;
    QPointer<RequestHandler> requestHandler;
    QFont m_font{"JetBrains Mono", 16};


    void formatUserInput(QListWidgetItem* item);
    void formatResponse(QListWidgetItem* item);

private slots:
    void onNewDataReceived(const QString& data);

};


#endif //GPTINTERFACE_WORKSPACE_H