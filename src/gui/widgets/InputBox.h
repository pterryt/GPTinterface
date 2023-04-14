#ifndef GPTINTERFACE_INPUTBOX_H
#define GPTINTERFACE_INPUTBOX_H

#include <QTextEdit>

class InputBox : public QTextEdit
{
Q_OBJECT

public:
    explicit InputBox(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void enterKeyPressed();

private:
    void adjustHeight();
};

#endif // GPTINTERFACE_INPUTBOX_H
