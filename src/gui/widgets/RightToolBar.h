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
    void clearContextButtonClick();

private:

    /* Pointer to the layout. */
    QVBoxLayout *m_layout;
    /* Pointer to send button. */
    QPushButton *m_sendButton;
    /* Pointer to the microphone button. */
    QPushButton *m_micButton;
    /* Pointer to the appends button. */
    QPushButton *m_optionsButton;
    /* Pointer to the clear context button. */
    QPushButton *m_clearContextButton;

private Q_SLOTS:

    void handleSendButtonClicked();
    void handleClearContextButtonClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // GPTINTERFACE_RIGHTTOOLBAR_H
