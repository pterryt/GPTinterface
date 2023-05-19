#ifndef GPTINTERFACE_SCSCROLLAREA_H
#define GPTINTERFACE_SCSCROLLAREA_H

#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUuid>
#include "scItem.h"

class scScrollArea : public QScrollArea
{
Q_OBJECT

public:

    explicit scScrollArea(QWidget *parent = nullptr);
    ~scScrollArea() override;

public Q_SLOTS:

    void createNewStaticContext();
    void rebuildStaticContext(const QString& id = QString(), const QString& text = QString());
    void handleItemDeleteRequested(QUuid id);

Q_SIGNALS:

protected:

private:
    QVBoxLayout *m_vlayout;
    QHash<QUuid, scItem*> *scUOMap;
    void saveItems();
    void loadItems();
};

#endif // GPTINTERFACE_SCSCROLLAREA_H
