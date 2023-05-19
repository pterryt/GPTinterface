#include "HistoryList.h"
#include <QCoreApplication>

HistoryList::HistoryList(QWidget *parent)
        : QListWidget(parent)
{
    m_historyDirectory = QDir(QCoreApplication::applicationDirPath() + "/saved_chats/");
    m_vLayout = new QVBoxLayout(this);
    setLayout(m_vLayout);
    m_vLayout->setSpacing(5);

    m_font = QFont("Arial");
    m_font.setPointSize(14);
    auto labelFont = QFont("Comic Sans MS");
    labelFont.setPointSize(25);

    auto *hLabel = new QLabel("History", this);
    hLabel->setFont(labelFont);
    hLabel->setMargin(8);
    m_vLayout->addWidget(hLabel);
    loadHistory();
    m_vLayout->addStretch();


    connect(
            GlobalMediator::instance(), &GlobalMediator::sendNewHistoryItem, this, &HistoryList::handleNewHistoryItemCreated
            );

}

void HistoryList::loadHistory()
{
            foreach (QFileInfo info, m_historyDirectory.entryInfoList())
        {
            if (info.isFile())
            {
                createButtonFromFile(info);
            }
        }
}

void HistoryList::createButtonFromFile(QFileInfo &info)
{
    auto* hb = new HistoryButton(this);
    QString buttonName = info.fileName();
    int index = buttonName.indexOf("_");
    buttonName = buttonName.right(buttonName.length() - index - 1); // exclude the underscore character
    index = buttonName.lastIndexOf(".json");
    buttonName = buttonName.left(index);
    hb->setMName(buttonName);
    hb->setMFile(info.filePath());
    hb->getMLabel()->setFont(m_font);
    m_vLayout->insertWidget(1, hb);
}

void HistoryList::handleNewHistoryItemCreated(QString &file)
{
    QFileInfo info = QFileInfo(file);
    createButtonFromFile(info);
}
