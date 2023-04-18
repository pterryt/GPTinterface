#ifndef GPTINTERFACE_AITEXT_H
#define GPTINTERFACE_AITEXT_H

#include "customTextEdit.h"

class aiText : public customTextEdit
{
    Q_OBJECT

public:

    explicit aiText(QWidget *parent = nullptr);

public Q_SLOTS:

private:

    QTextDocument *m_doc = this->document();
};

#endif // GPTINTERFACE_AITEXT_H
