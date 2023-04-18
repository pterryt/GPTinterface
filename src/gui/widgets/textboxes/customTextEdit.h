#ifndef SCROLLTEST_H
#define SCROLLTEST_H

#define QT_NO_KEYWORDS
#include <QTextEdit>

class customTextEdit : public QTextEdit
{
    Q_OBJECT

public:

    explicit customTextEdit(QWidget *parent = nullptr);

/*
    bool isCodeBlock();

    void setCodeBlock(bool isCodeBlock);
*/

    Q_SIGNALS:

    void newLineAppended();


public Q_SLOTS:

    virtual void appendText(const QString &text);

    void updateSizeHint();

private:

};

#endif // SCROLLTEST_H
