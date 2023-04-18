#include "customTextEdit.h"
#include <QShortcut>
#include "../RightToolBar.h"


customTextEdit::customTextEdit(QWidget *parent)
        : QTextEdit(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setReadOnly(true);

}


void customTextEdit::appendText(const QString &text)
{
   insertPlainText(text);
   updateSizeHint();
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
