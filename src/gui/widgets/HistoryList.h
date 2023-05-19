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
#include "history/HistoryButtonMenu.h"


class HistoryButton : public QPushButton
{
Q_OBJECT

public:

    explicit HistoryButton(QWidget *parent = nullptr) : QPushButton(parent)
    {
        hLayout = new QHBoxLayout(this);
        hLayout->setContentsMargins(0, 0, 0, 0);
        buttonPTR = this;
        setContextMenuPolicy(Qt::CustomContextMenu);
        m_rClickMenu = new HistoryButtonMenu(this);
        setStyleSheet("QPushButton {padding: 7px 0;}");

        connect(
                this, &QPushButton::clicked, this, &HistoryButton::handleHistoryButtonClicked
        );
        connect(
                this, &QPushButton::customContextMenuRequested,
                this, &HistoryButton::handleButtonRightClicked);
        connect(
                m_rClickMenu->deleteButton, &QAction::triggered, this,
                &HistoryButton::handleDeleteActionClicked);
    }

//    ~HistoryButton() override
//    {
//        buttonPTR->deleteLater();
//    }

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

    void sendHistoryItem(const QString &file);

public Q_SLOTS:

    void handleHistoryButtonClicked()
    {
//        Q_EMIT sendHistoryItem(m_File);
        Q_EMIT GlobalMediator::instance()->sendHistoryButtonClicked(buttonPTR);
    }

    void handleButtonRightClicked(const QPoint &pos)
    {
        qDebug() << "Right-clicked on button";
        m_rClickMenu->exec(mapToGlobal(pos));
    }

    void handleDeleteActionClicked()
    {
        QFile hFile = QFile(getMFile());
        if (hFile.exists())
        {
            hFile.remove();
        }
        deleteLater();
    }

private:

    QLabel *m_Label;
    HistoryButtonMenu *m_rClickMenu = nullptr;

public:

    HistoryButtonMenu *getMRClickMenu() const
    {
        return m_rClickMenu;
    }

    QLabel *getMLabel() const
    {
        return m_Label;
    }

    const QString &getMFile() const
    {
        return m_File;
    }

private:

    QString m_File;
    QPointer<HistoryButton> buttonPTR = nullptr;
    QHBoxLayout *hLayout;

};

/* HISTORY LIST CLASS STARTS */

class HistoryList : public QListWidget
{
Q_OBJECT

public:

    explicit HistoryList(QWidget *parent = nullptr);

public Q_SLOTS:

    void loadHistory();

    void handleNewHistoryItemCreated(QString &file);

private:

    void createButtonFromFile(QFileInfo &file);

    QVBoxLayout *m_vLayout;
    QDir m_historyDirectory;
    QFont m_font;
};


#endif // GPTINTERFACE_HISTORYLIST_H

