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

    [[nodiscard]] const QUuid &getMId() const;
    QString getText();
    void setText(const QString& text);
    void setCombo(int index);
    void setEnabled();
    void setDisabled();
    void setTextLocked();
    void setTextUnlocked();

public Q_SLOTS:

    void handleSCToggled(int enabled);
    void handleSCComboBoxChanged(int index);
    void handleDeleteButtonClicked();
    void handleEditButtonClicked();
    void handleUpButtonPressed();
    void handleDownButtonPressed();

Q_SIGNALS:

protected:

private:
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
