#ifndef SCROLLTEST_H
#define SCROLLTEST_H

#define QT_NO_KEYWORDS
#include <QTextEdit>

class customTextEdit : public QTextEdit
{
Q_OBJECT

public:
    explicit customTextEdit(const QString &text, QWidget *parent = nullptr);

public Q_SLOTS:
    void appendText(const QString &text);

    void updateSizeHint();
};

#endif // SCROLLTEST_H
