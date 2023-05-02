#ifndef GPTINTERFACE_CODEBLOCK_H
#define GPTINTERFACE_CODEBLOCK_H

#include "customTextEdit.h"
#include "../../../../QSourceHighlite/qsourcehighliter.h"

class codeBlock : public customTextEdit
{
    Q_OBJECT

public:

    explicit codeBlock(const int wsIndex, QWidget *parent = nullptr);

public Q_SLOTS:

//    void appendText(const QString &text) override;

private:
    QSourceHighlite::QSourceHighliter *m_syntaxHL;
    QTextDocument *m_doc = this->document();
};

#endif // GPTINTERFACE_CODEBLOCK_H
