#ifndef GPTINTERFACE_RIGHTTOOLBAR_H
#define GPTINTERFACE_RIGHTTOOLBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class RightToolBar : public QWidget
{
Q_OBJECT

public:
    explicit RightToolBar(QWidget *parent = nullptr);
private:
    QVBoxLayout *m_layout;
    QPushButton *m_sendButton;
    QPushButton *m_micButton;
    QPushButton *m_optionsButton;
};

#endif // GPTINTERFACE_RIGHTTOOLBAR_H
