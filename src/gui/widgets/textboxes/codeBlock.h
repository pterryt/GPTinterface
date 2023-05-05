#ifndef GPTINTERFACE_CODEBLOCK_H
#define GPTINTERFACE_CODEBLOCK_H

#include "customTextEdit.h"
#include "../../../../QSourceHighlite/qsourcehighliter.h"

class codeBlock : public customTextEdit
{
    Q_OBJECT

public:

    explicit codeBlock(const int wsIndex, QWidget *parent = nullptr);

private:

    QSourceHighlite::QSourceHighliter *m_syntaxHL;
    QTextDocument *m_doc = this->document();
};

#endif // GPTINTERFACE_CODEBLOCK_H
