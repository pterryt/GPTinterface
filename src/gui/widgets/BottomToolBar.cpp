#include "BottomToolBar.h"
#include <QHBoxLayout>
#include "../../utils/GlobalMediator.h"

BottomToolBar::BottomToolBar(QWidget *parent)
        : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    auto *hlayout = new QHBoxLayout(this);
    hlayout->setContentsMargins(0,0,0,0);
    hlayout->setSpacing(0);
    hlayout->addStretch();
    m_sumContextualTokens = new QLabel("contextual", this);
    m_currentInputTokens = new QLabel("current", this);
    m_sumContextualTokens->setStyleSheet("border: 1px solid red;");

    QFont font = QFont("JetBrains Mono");
    font.setPointSize(12);
    m_sumContextualTokens->setFont(font);
    m_currentInputTokens->setFont(font);

    setStyleSheet("border:1px solid red;");

    hlayout->addWidget(m_sumContextualTokens);
    hlayout->addWidget(m_currentInputTokens);
    setLayout(hlayout);
//    setLayout(hlayout);


}


void BottomToolBar::setCurrentInputTokens(int count)
{
    m_currentInputTokens->setText("Input Tokens: " + QString::number(count));
}
