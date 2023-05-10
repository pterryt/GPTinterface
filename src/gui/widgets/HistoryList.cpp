#include "HistoryList.h"
#include <QCoreApplication>

HistoryList::HistoryList(QWidget *parent)
        : QListWidget(parent)
{
    m_historyDirectory = QDir(QCoreApplication::applicationDirPath() + "/saved_chats/");
    m_vLayout = new QVBoxLayout(this);
    setLayout(m_vLayout);
    m_vLayout->setSpacing(0);
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
    m_vLayout->insertWidget(0, hb);
}

void HistoryList::handleNewHistoryItemCreated(QString &file)
{
    QFileInfo info = QFileInfo(file);
    createButtonFromFile(info);
}
