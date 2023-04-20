#include "BottomToolBar.h"
#include <QHBoxLayout>
#include "../../utils/GlobalMediator.h"

BottomToolBar::BottomToolBar(QWidget *parent)
        : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto *hlayout = new QHBoxLayout(this);
    hlayout->setSpacing(25);

    m_sumContextualTokens = new QLabel("Context: 0", parent);
    m_sumContextualTokens->setSizePolicy(QSizePolicy::Preferred,
                                         QSizePolicy::Preferred);
    m_currentInputTokens = new QLabel("Input: 0", parent);
    m_currentInputTokens->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QFont font = QFont("JetBrains Mono");
    font.setPointSize(12);
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