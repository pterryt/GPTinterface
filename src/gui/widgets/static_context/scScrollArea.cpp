#include "scScrollArea.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>
#include <QFile>

#include "../../../devtools/logger.h"
#include "../../../utils/GlobalMediator.h"


scScrollArea::scScrollArea(QWidget *parent)
        : QScrollArea(parent)
{
    GlobalMediator::instance()->setScScrollArea(this);
    scUOMap = new QHash<QUuid, scItem *>();
    auto *content = new QWidget(this);
    setWidgetResizable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWidget(content);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    m_vlayout = new QVBoxLayout(content);
    m_vlayout->addStretch();
    content->setLayout(m_vlayout);
    loadItems();

    connect(
            GlobalMediator::instance(), &GlobalMediator::sendNewStaticContextButtonClicked,
            this, &scScrollArea::createNewStaticContext
    );

    connect(
            GlobalMediator::instance(), &GlobalMediator::sendItemDeleteRequested,
            this, &scScrollArea::handleItemDeleteRequested
    );
    connect(
            GlobalMediator::instance(), &GlobalMediator::sendScItemMoveUpButtonClicked,
            this, &scScrollArea::handleItemMoveUpButtonClicked
            );
}

scScrollArea::~scScrollArea()
{
    saveItems();
    delete scUOMap;
}

void scScrollArea::createNewStaticContext()
{
    auto *widget = new QWidget(this);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    auto *layout = new QHBoxLayout(widget);
    auto *item = new scItem(widget);
    item->setTextUnlocked();
    scUOMap->insert(item->getMId(), item);
    layout->addWidget(item);
    widget->setObjectName("object");
    widget->setStyleSheet("#object {border: 1px solid black;} ");
    m_vlayout->insertWidget(0, widget);
}

void scScrollArea::saveItems()
{
    QJsonDocument doc;
    QJsonArray arr;
    for (auto &item: *scUOMap)
    {
        QString iText = item->getText();
        if (iText != "")
        {
            QJsonObject obj;
            obj["id"] = item->getMId().toString();
            obj["text"] = iText;
            arr.append(obj);
        }
    }
    doc.setArray(arr);
    QString saveLoc = QCoreApplication::applicationDirPath() + "/static_contexts/";
    QString filename = "saved_contexts.json";
    filename = saveLoc + filename;
    QFile Jsonfile(filename);
    if (Jsonfile.open(QIODevice::WriteOnly))
    {
        if (Jsonfile.write(doc.toJson()) == -1)
        {
            giLog::consoleLog->error("Saving static contexts failed.");
        }
        Jsonfile.close();
    }
}

void scScrollArea::handleItemDeleteRequested(QUuid id)
{
    scUOMap->value(id)->parentWidget()->deleteLater();
    scUOMap->remove(id);
}

void scScrollArea::loadItems()
{
    QString saveLoc = QCoreApplication::applicationDirPath() + "/static_contexts/";
    QString filename = "saved_contexts.json";
    filename = saveLoc + filename;
    QFile hFile = QFile(filename);
    hFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument jDoc = QJsonDocument::fromJson(hFile.readAll());
    QJsonArray arr = jDoc.array();

    for (auto &&i: arr)
    {
        QJsonObject obj = i.toObject();
        rebuildStaticContext(obj["id"].toString(), obj["text"].toString());
    }
}

void scScrollArea::rebuildStaticContext(const QString &id, const QString &text)
{
    auto *widget = new QWidget(this);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    auto *layout = new QHBoxLayout(widget);
    auto *item = new scItem(widget, id);
    item->setText(text);
    scUOMap->insert(item->getMId(), item);
    layout->addWidget(item);
    widget->setObjectName("object");
    widget->setStyleSheet("#object {border: 1px solid black;} ");
    m_vlayout->insertWidget(0, widget);
    widget->setLayout(layout);
}

QHash<QUuid, scItem *> *scScrollArea::getscUOMap()
{
    return scUOMap;
}

void scScrollArea::loadStaticContexts(QHash<QUuid, int> *workspaceSettings)
{
    QHash<QUuid, scItem *>::iterator i;
    for (i = scUOMap->begin(); i != scUOMap->end(); ++i)
    {
        i.value()->setDisabled();
    }
    QHash<QUuid, int>::iterator it;
    for (it = workspaceSettings->begin(); it != workspaceSettings->end(); ++it)
    {
        QUuid key = it.key();
        int comboValue = it.value();
        if (scUOMap->contains(key))
        {
            scUOMap->value(key)->setCombo(comboValue);
            scUOMap->value(key)->setEnabled();
        }
        else
        {
            workspaceSettings->remove(key);
        }
    }
}

void scScrollArea::handleItemMoveDownButtonClicked(int index)
{
    if (index != m_vlayout->count() - 1)
    {
        QWidget *widget = m_vlayout->itemAt(index)->widget();
        m_vlayout->takeAt(index);
        m_vlayout->insertWidget(index + 1, widget);
    }
}

void scScrollArea::handleItemMoveUpButtonClicked(int index)
{
    if (index != 0)
    {
        QWidget *widget = m_vlayout->itemAt(index)->widget();
        m_vlayout->takeAt(index);
        m_vlayout->insertWidget(index - 1, widget);
    }
}





