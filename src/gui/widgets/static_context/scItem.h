#ifndef GPTINTERFACE_SCITEM_H
#define GPTINTERFACE_SCITEM_H

#include <QWidget>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QUuid>

class scItem : public QWidget {
Q_OBJECT

public:
    explicit scItem(QWidget *parent = nullptr, const QString& id = QString());
    const QUuid &getMId() const;
    void setEditted();
    QString getText();
    void setText(const QString& text);

public Q_SLOTS:
    void toggleCanEdit();
    void handleSCToggled(int enabled);
    void handleSCComboBoxChanged(int index);
    void handleTextChanged();
    void handleDeleteButtonClicked();

Q_SIGNALS:

protected:

private:
    bool editted = false;
    bool canEdit = false;
    QUuid m_id;
    QHBoxLayout *m_layout;
    QCheckBox *m_checkBox;
    QPlainTextEdit *m_textEdit;
    QComboBox *m_comboBox;
    QPushButton *m_editButton;


    QVBoxLayout *m_arrowHolder;
    QPushButton *m_moveUpButton;
    QPushButton *m_moveDownButton;
    QPushButton *m_deleteButton;
};

#endif // GPTINTERFACE_SCITEM_H
