#ifndef GPTINTERFACE_HISTORYLIST_H
#define GPTINTERFACE_HISTORYLIST_H

#include <QListWidget>
#include <QPushButton>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QVBoxLayout>
#include <QPointer>

#include "../../utils/GlobalMediator.h"


class HistoryButton : public QPushButton
{
    Q_OBJECT

public:

    explicit HistoryButton(QWidget *parent = nullptr) : QPushButton(parent)
    {
        hLayout = new QHBoxLayout(this);
        hLayout->setContentsMargins(0,0,0,0);
        buttonPTR = this;
        connect(
                this, &QPushButton::clicked, this, &HistoryButton::handleHistoryButtonClicked
                );
    }

    ~HistoryButton() override
    {
        buttonPTR->deleteLater();
    }

    void setMName(const QString &name)

    {
        m_Label = new QLabel(name, this);
        hLayout->addWidget(m_Label);
        m_Label->setAlignment(Qt::AlignCenter);
    }

    void setMFile(const QString &file)
    {
        m_File = file;
    }

    Q_SIGNALS:

    void sendHistoryItem(const QString& file);

public Q_SLOTS:

    void handleHistoryButtonClicked()
    {
//        Q_EMIT sendHistoryItem(m_File);
        Q_EMIT GlobalMediator::instance()->sendHistoryButtonClicked(buttonPTR);
    }

private:

    QLabel *m_Label;
    QString m_File;
    QPointer<HistoryButton> buttonPTR = nullptr;

public:

    const QString &getMFile() const
    {
        return m_File;
    }

private:
    QHBoxLayout *hLayout;

};

class HistoryList : public QListWidget
{
    Q_OBJECT

public:

    explicit HistoryList(QWidget *parent = nullptr);

public Q_SLOTS:

    void loadHistory();
    void handleNewHistoryItemCreated(QString& file);

private:

    void createButtonFromFile(QFileInfo& file);
    QVBoxLayout *m_vLayout;
    QDir m_historyDirectory;
};




#endif // GPTINTERFACE_HISTORYLIST_H

