#include "InputBox.h"

InputBox::InputBox(QWidget *parent)
        : QTextEdit(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setLineWrapMode(QTextEdit::WidgetWidth);
    setWordWrapMode(QTextOption::WrapAnywhere);


    connect(this, &QTextEdit::textChanged, this, &InputBox::adjustHeight);
}

void InputBox::resizeEvent(QResizeEvent *event)
{
    adjustHeight();
    QTextEdit::resizeEvent(event);
}

void InputBox::adjustHeight()
{
    QFontMetrics fm(font());
    int lineHeight = fm.height();
    int contentLines = document()->size().height() / lineHeight;

    if (contentLines <= 0)
    {
        contentLines = 1;
    }

    // if we hit maxLines turn on scrolling
    int maxLines = 10;
    if (contentLines > maxLines)
    {
        contentLines = maxLines;
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
    else
    {
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    int frameWidth = lineWidth() * 2;
    int newHeight = contentLines * lineHeight + 2 * contentsMargins().top() +
            frameWidth;

    setFixedHeight(newHeight);
}