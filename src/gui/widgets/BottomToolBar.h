#ifndef GPTINTERFACE_BOTTOMTOOLBAR_H
#define GPTINTERFACE_BOTTOMTOOLBAR_H

#include <QWidget>
#include <QLabel>

class BottomToolBar : public QWidget
{
Q_OBJECT

public:
    explicit BottomToolBar(QWidget *parent = nullptr);
    void setTokenCounts(const int sumTokens, const int inputTokens);

private:
    QLabel *m_sumContextualTokens;
    QLabel *m_currentInputTokens;


};

#endif // GPTINTERFACE_BOTTOMTOOLBAR_H
