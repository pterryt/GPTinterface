#ifndef GPTINTERFACE_LEFTTOOLBAR_H
#define GPTINTERFACE_LEFTTOOLBAR_H

#define QT_NO_KEYWORDS
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class LeftToolBar : public QWidget
{
Q_OBJECT

public:

    explicit LeftToolBar(QWidget *parent = nullptr);

Q_SIGNALS:

    void sendHistoryButtonClicked();

private:
    QVBoxLayout *m_layout;
    QPushButton *m_historyButton;

private Q_SLOTS:

    void handleHistoryButtonClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // GPTINTERFACE_LEFTTOOLBAR_H
