#ifndef SCROLLTEST_H
#define SCROLLTEST_H

#include <QTextEdit>

class customTextEdit : public QTextEdit
{
Q_OBJECT

public:
    explicit customTextEdit(const QString &text, QWidget *parent = nullptr);

public slots:
    void appendText(const QString &text);

    void updateSizeHint();
};

#endif // SCROLLTEST_H
