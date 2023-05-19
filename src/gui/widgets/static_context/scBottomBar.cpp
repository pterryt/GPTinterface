#include <QVBoxLayout>
#include "scBottomBar.h"
#include "../../../utils/GlobalMediator.h"
#include "QCoreApplication"

scBottomBar::scBottomBar(QWidget *parent)
        : QWidget(parent)
{

    QIcon addIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/add.png");
    auto *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    m_label = new QLabel("Static Contexts", this);
    QFont font = QFont("Comic Sans MS");
    font.setPointSize(16);
    m_label->setFont(font);
    m_label->setStyleSheet("padding-left:10px;");
    m_newStaticContextButton = new QPushButton(this);
    m_newStaticContextButton->setIcon(addIcon);
    m_newStaticContextButton->setFixedSize(40,40);
    m_newStaticContextButton->setIconSize(QSize(30,30));
    setLayout(layout);
    layout->addWidget(m_label);
    layout->addWidget(m_newStaticContextButton);


    connect(
            m_newStaticContextButton, &QPushButton::pressed, this, &scBottomBar::newButtonPressed
            );
}

void scBottomBar::newButtonPressed()
{
    Q_EMIT GlobalMediator::instance()->sendNewStaticContextButtonClicked();
}
