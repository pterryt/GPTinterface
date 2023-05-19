#ifndef GPTINTERFACE_SCBOTTOMBAR_H
#define GPTINTERFACE_SCBOTTOMBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class scBottomBar : public QWidget
{
Q_OBJECT

public:

    explicit scBottomBar(QWidget* parent = nullptr);

public Q_SLOTS:
    void newButtonPressed();

Q_SIGNALS:

protected:

private:
    QPushButton *m_newStaticContextButton;
    QLabel *m_label;
};

#endif // GPTINTERFACE_SCBOTTOMBAR_H
