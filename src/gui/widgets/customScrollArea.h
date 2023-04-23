#ifndef GPTINTERFACE_CUSTOMSCROLLAREA_H
#define GPTINTERFACE_CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextDocument>

class customScrollArea : public QScrollArea
{
Q_OBJECT

public:

    explicit customScrollArea(QWidget *parent = nullptr);
    void addCustomWidget(QWidget* widget);
    void updateScrollPosition();

private:

    QVBoxLayout *m_vLayout;
    QScrollBar *m_vScrollBar;

protected:

    void resizeEvent(QResizeEvent *event) override;
};

#endif // GPTINTERFACE_CUSTOMSCROLLAREA_H
