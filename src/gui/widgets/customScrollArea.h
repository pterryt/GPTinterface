#ifndef GPTINTERFACE_CUSTOMSCROLLAREA_H
#define GPTINTERFACE_CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextDocument>
#include <QPointer>
#include "HistoryList.h"
#include "textboxes/customTextEdit.h"

class customScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit customScrollArea(QWidget *parent = nullptr);
    ~customScrollArea() override;
    void addCustomWidget(customTextEdit* widget);
    void updateScrollPosition();
    int textBoxCount = 0;
    bool hasChanged = false;
    bool isHistoric = false;
    QPointer<HistoryButton> hButton;

public Q_SLOTS:

    void handleSetWSName(const QString &name);

private:

    QVBoxLayout *m_vLayout;
    QScrollBar *m_vScrollBar;
    /* List of pointers to objects to be used for json caching. */
    QVector<QPair<customTextEdit::bType, customTextEdit*>> textEditList;
    void saveConversation();
    QString wsName = "";
    void deleteConversation();

protected:

    void resizeEvent(QResizeEvent *event) override;
};

#endif // GPTINTERFACE_CUSTOMSCROLLAREA_H

