#ifndef GPTINTERFACE_USERTEXT_H
#define GPTINTERFACE_USERTEXT_H

#include "customTextEdit.h"

class userText : public customTextEdit
{
    Q_OBJECT

public:

    explicit userText(int wsIndex, QWidget *parent = nullptr);

private:

    QTextDocument *m_doc = this->document();

};

#endif // GPTINTERFACE_USERTEXT_H
