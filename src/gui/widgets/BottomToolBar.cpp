#include "BottomToolBar.h"

#include <QHBoxLayout>


BottomToolBar::BottomToolBar(QWidget *parent)
        : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto *hlayout = new QHBoxLayout(this);
    hlayout->setSpacing(25);

    m_sumContextualTokens = new QLabel("No Context", parent);
    m_sumContextualTokens->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    m_currentInputTokens = new QLabel("Input: 0", parent);
    m_currentInputTokens->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QFont font = QFont("Arial");
    font.setPointSize(10);
    m_sumContextualTokens->setFont(font);
    m_currentInputTokens->setFont(font);

    hlayout->addWidget(m_sumContextualTokens);
    hlayout->addWidget(m_currentInputTokens);

    setLayout(hlayout);
}

void BottomToolBar::setInputTokens(int count)
{
    m_currentInputTokens->setText("Input: " + QString::number(count));
}

void BottomToolBar::setContextTokens(int count)
{
    m_sumContextualTokens->setText("Context: " + QString::number
    (count));
}

void BottomToolBar::handleTabChanged(int input, int context)
{
    setInputTokens(input);
    setContextTokens(context);
}