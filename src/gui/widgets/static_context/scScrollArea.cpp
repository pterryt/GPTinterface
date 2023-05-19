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
    scUOMap = new QHash<QUuid, scItem*>();
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
    item->setEditted();
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
    for (auto &item : *scUOMap)
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
    QString filename =  "saved_contexts.json";
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
    QString filename =  "saved_contexts.json";
    filename = saveLoc + filename;
    QFile hFile = QFile(filename);
    hFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument jDoc = QJsonDocument::fromJson(hFile.readAll());
    QJsonArray arr = jDoc.array();

    for (auto && i : arr)
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
}





