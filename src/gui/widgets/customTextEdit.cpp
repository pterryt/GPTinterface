#include "customTextEdit.h"
#include <QShortcut>
#include "RightToolBar.h"


customTextEdit::customTextEdit(const QString &text, QWidget *parent)
        : QTextEdit(text, parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    setLineWrapMode(QTextEdit::NoWrap);
    setReadOnly(true);

    QFont font = QFont("JetBrains Mono");
    font.setPointSize(22);
    setFont(font);
    updateSizeHint();

}


void customTextEdit::appendText(const QString &text)
{
    insertPlainText(text);
}

void customTextEdit::updateSizeHint()
{
    document()->adjustSize();

    int contentsMarginsTop = contentsMargins().top();
    int contentsMarginsBottom = contentsMargins().bottom();

    int height = document()->size().height() + contentsMarginsBottom +
            contentsMarginsTop;

    setMinimumHeight(height);
    setMaximumHeight(height);
    updateGeometry();

}
