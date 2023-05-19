#include "scItem.h"
#include <QCoreApplication>
#include "../../../utils/GlobalMediator.h"

scItem::scItem(QWidget *parent, const QString& id)
        : QWidget(parent)
{
    if (!id.isEmpty())
    {
        m_id = QUuid(id);
    }
    else
    {
        m_id = QUuid::createUuid();
    }
    QIcon editIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/edit.png");
    QIcon downArrowIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/down-filled-triangular-arrow.png");
    QIcon upArrowIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/up-filled-triangular-arrow.png");
    QString redDeleteIconPath = QCoreApplication::applicationDirPath() + "/../icon/x.png";
    QIcon redDeleteIcon = QIcon(redDeleteIconPath);
    QIcon blackDeleteIcon = QIcon(QCoreApplication::applicationDirPath() + "/../icon/xb.png");
    auto font = QFont("Arial");
    font.setPointSize(16);

    setFixedHeight(100);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_layout = new QHBoxLayout(this);
    m_layout->setSpacing(10);

    m_checkBox = new QCheckBox(this);
    m_checkBox->setStyleSheet("QCheckBox {background-color:#252525;padding:0px;spacing:0px;} QCheckBox::indicator {width: 20px; height: 20px;}");

    m_textEdit = new QPlainTextEdit(this);
    m_textEdit->setStyleSheet("background:#252525;");
    m_textEdit->setFont(font);

    m_comboBox = new QComboBox(this);
    m_comboBox->setFixedSize(100,35);
    m_comboBox->setStyleSheet("background:#252525;");
    m_comboBox->addItem("Prefix");
    m_comboBox->addItem("Prefix-All");
    m_comboBox->addItem("Suffix");
    m_comboBox->addItem("Suffix-All");
    m_comboBox->setFont(font);

    m_editButton = new QPushButton(this);
    m_editButton->setStyleSheet("background:#252525;");
    m_editButton->setFixedSize(35,35);
    m_editButton->setIcon(editIcon);

    auto *arrowBox = new QWidget(this);
    m_arrowHolder = new QVBoxLayout(arrowBox);
    m_moveUpButton = new QPushButton(this);
    m_moveUpButton->setStyleSheet("background:#252525;");
    m_moveUpButton->setIcon(upArrowIcon);
    m_moveDownButton = new QPushButton(this);
    m_moveDownButton->setStyleSheet("background:#252525;");
    m_moveDownButton->setIcon(downArrowIcon);
    m_arrowHolder->addWidget(m_moveUpButton);
    m_arrowHolder->addWidget(m_moveDownButton);
    arrowBox->setLayout(m_arrowHolder);
    m_arrowHolder->setSpacing(0);

    m_deleteButton = new QPushButton(this);
    m_deleteButton->setIcon(blackDeleteIcon);
    m_deleteButton->setIconSize(QSize(10,10));
    m_deleteButton->setStyleSheet("QPushButton { border: none; } QPushButton::hover { border-image:url(" + redDeleteIconPath + "); }");


    m_layout->addWidget(m_checkBox);
    m_layout->addWidget(m_textEdit);
    m_layout->addWidget(m_comboBox);
    m_layout->addWidget(m_editButton);
    m_layout->addWidget(arrowBox);
    m_layout->addWidget(m_deleteButton, 0, Qt::AlignTop);

    connect(m_editButton, &QPushButton::pressed, this, &scItem::toggleCanEdit);
    connect(m_checkBox, &QCheckBox::stateChanged, this, &scItem::handleSCToggled);
    connect(m_comboBox, &QComboBox::currentIndexChanged, this, &scItem::handleSCComboBoxChanged);
    connect(m_textEdit, &QPlainTextEdit::textChanged, this, &scItem::handleTextChanged);
    connect(m_deleteButton, &QPushButton::pressed, this, &scItem::handleDeleteButtonClicked);
}

void scItem::toggleCanEdit()
{
    canEdit = !canEdit;
}

const QUuid &scItem::getMId() const
{
    return m_id;
}

void scItem::handleSCToggled(int enabled)
{
    Q_EMIT GlobalMediator::instance()->sendSCToggled(m_id, enabled);
}

void scItem::handleSCComboBoxChanged(int index)
{
    Q_EMIT GlobalMediator::instance()->sendSCComboBoxChanged(m_id, index);
}

void scItem::handleTextChanged()
{
    editted = true;
}

void scItem::setEditted()
{
    editted = true;
}

QString scItem::getText()
{
    return m_textEdit->toPlainText();
}

void scItem::handleDeleteButtonClicked()
{
    Q_EMIT GlobalMediator::instance()->sendItemDeleteRequested(m_id);
}

void scItem::setText(const QString &text)
{
    m_textEdit->setPlainText(text);
}

