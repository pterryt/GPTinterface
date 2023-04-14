#ifndef GPTINTERFACE_CUSTOMSCROLLAREA_H
#define GPTINTERFACE_CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QVBoxLayout>

class customScrollArea : public QScrollArea
{
Q_OBJECT

public:
    explicit customScrollArea(QWidget *parent = nullptr);
    void addCustomWidget(QWidget* widget);

private:
    QVBoxLayout* m_vLayout;
};

#endif // GPTINTERFACE_CUSTOMSCROLLAREA_H
