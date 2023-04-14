#include "customTextEdit.h"
#include <QShortcut>
#include "RightToolBar.h"


customTextEdit::customTextEdit(const QString &text, QWidget *parent)
        : QTextEdit(text, parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setReadOnly(true);
    setFont(QFont("JetBrains Mono"));

}


void customTextEdit::appendText(const QString &text)
{
    insertPlainText(text);
}

void customTextEdit::updateSizeHint()
{
    int contentsMarginsTop = contentsMargins().top();
    int contentsMarginsBottom = contentsMargins().bottom();
    int height = document()->size().height() + contentsMarginsBottom +
            contentsMarginsBottom;
    setMinimumHeight(height);
    setMaximumHeight(height);
    updateGeometry();

}
