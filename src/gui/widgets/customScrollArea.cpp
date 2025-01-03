#include "customScrollArea.h"
#include <QScrollBar>
#include <QResizeEvent>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDateTime>
#include "../../utils/GlobalMediator.h"


customScrollArea::customScrollArea(QWidget *parent)
        : QScrollArea(parent)
{
    setContentsMargins(0,0,0,0);
    auto *scrollAreaContent = new QWidget(this);
    setWidget(scrollAreaContent);
    scrollAreaContent->setContentsMargins(0,0,0,0);
    scrollAreaContent->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Preferred);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    auto *spacer =
            new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_vLayout = new QVBoxLayout(scrollAreaContent);
    m_vLayout->addItem(spacer);
    m_vLayout->setSpacing(0);
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayout->addStretch();
    scrollAreaContent->setLayout(m_vLayout);

    m_vScrollBar = verticalScrollBar();

}

void customScrollArea::addCustomWidget(customTextEdit *widget)
{
    m_vLayout->insertWidget(m_vLayout->count() - 2, widget);
    widget->setFixedWidth(size().width());
    widget->convoIndex = textBoxCount;
    QPair<customTextEdit::bType, customTextEdit*> pair;
    pair.first = widget->getBtype();
    pair.second = widget;
    textEditList.push_back(pair);
    ++textBoxCount;
    hasChanged = true;
}

void customScrollArea::updateScrollPosition()
{
    m_vScrollBar->setValue(m_vScrollBar->maximum());
}

void customScrollArea::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    int updatedWidth = event->size().width();
    for (int i = 0; i < m_vLayout->count() - 1; ++i)
    {
        customTextEdit *widget = qobject_cast<customTextEdit *>(m_vLayout->itemAt(i)
                ->widget());
        if (widget)
        {
            widget->setFixedWidth(updatedWidth);
            widget->updateSizeHint();

        }
    }
}

void customScrollArea::saveConversation()
{
    bool saveSuccess = false;
    if (!textEditList.isEmpty() && hasChanged)
    {
        /* Get time for unique naming purposes. */
        QString time = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");
        /* Create the QDoc. */
        QJsonDocument doc;
        QJsonArray arr;
        QJsonObject pageName;
        pageName["name"] = wsName == "" ? time : wsName;
        arr.append(pageName);

        for (QPair<customTextEdit::bType, customTextEdit*> cte : textEditList)
        {
            QJsonObject obj;
            obj["type"] = cte.first;
            obj["text"] = cte.second->toPlainText();
            arr.append(obj);
        }
        doc.setArray(arr);

       /* Save the QDoc to a file. */

       QString saveLoc = QCoreApplication::applicationDirPath() + "/saved_chats/";
       QString filename =  time + "_" + wsName + ".json";
       filename = saveLoc + filename;
       QFile Jsonfile(filename);
      if (Jsonfile.open(QIODevice::WriteOnly))
       {
           if (Jsonfile.write(doc.toJson()) != -1)
           {
               saveSuccess = true;
           }
           Jsonfile.close();
           if (!GlobalMediator::instance()->isMShuttingDown())
           {
               Q_EMIT GlobalMediator::instance()->sendNewHistoryItem(filename);
           }
       }
    }
    if (isHistoric && saveSuccess)
    {
        deleteConversation();
    }
}

void customScrollArea::deleteConversation()
{
    QFile hFile = QFile(hButton->getMFile());
    if (hFile.exists()){
        hFile.remove();
    }
    if (!hButton.isNull())
    {
        hButton->deleteLater();
    }
}

void customScrollArea::handleSetWSName(const QString &name)
{
    wsName = name;
}

customScrollArea::~customScrollArea()
{
    saveConversation();
}


