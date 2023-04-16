#ifndef GPTINTERFACE_INPUTBOX_H
#define GPTINTERFACE_INPUTBOX_H

#define QT_NO_KEYWORDS
#include <QTextEdit>

class InputBox : public QTextEdit
{
Q_OBJECT

public:
    explicit InputBox(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;

Q_SIGNALS:
    void enterKeyPressed();

private:
    void adjustHeight();
};

#endif // GPTINTERFACE_INPUTBOX_H
