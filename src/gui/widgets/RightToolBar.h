#ifndef GPTINTERFACE_RIGHTTOOLBAR_H
#define GPTINTERFACE_RIGHTTOOLBAR_H

#define QT_NO_KEYWORDS
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class RightToolBar : public QWidget
{
Q_OBJECT

public:

    explicit RightToolBar(QWidget *parent = nullptr);

Q_SIGNALS:

    void sendButtonClick();

private:
    QVBoxLayout *m_layout;
    QPushButton *m_sendButton;
    QPushButton *m_micButton;
    QPushButton *m_optionsButton;

private Q_SLOTS:

    void handleSendButtonClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // GPTINTERFACE_RIGHTTOOLBAR_H
