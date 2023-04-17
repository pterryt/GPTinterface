#include "customTextEdit.h"
#include <QShortcut>
#include <QTextBlock>
#include "RightToolBar.h"


customTextEdit::customTextEdit(const QString &text, QWidget *parent)
        : QTextEdit(text, parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setLineWrapMode(QTextEdit::WidgetWidth);
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

/*void customTextEdit::updateSizeHint() {
    QTextDocument *doc = document();
    QFontMetricsF fm(font());
    qreal lineHeight = fm.lineSpacing();

    int visualLines = 1;
    for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next()) {
        qreal blockWidth = fm.horizontalAdvance(it.text());
        visualLines += std::ceil(blockWidth / (width() - (contentsMargins().left() + contentsMargins().right())));
    }

    int contentsMarginsTop = contentsMargins().top();
    int contentsMarginsBottom = contentsMargins().bottom();

    int height = visualLines * lineHeight + contentsMarginsTop + contentsMarginsBottom;

    setMinimumHeight(height);
    setMaximumHeight(height);
    updateGeometry();
}*/

/*void customTextEdit::updateSizeHint()
{
    QTextDocument *doc = document();
    QFontMetricsF fm(font());
    qreal lineHeight = fm.lineSpacing();

    int visualLines = 1;
    for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next()) {
        qreal blockWidth = fm.horizontalAdvance(it.text());
        visualLines += std::ceil(blockWidth / (viewport()->width() - (contentsMargins().left() + contentsMargins().right())));
    }

    int contentsMarginsTop = contentsMargins().top();
    int contentsMarginsBottom = contentsMargins().bottom();

    int height = (visualLines * lineHeight) - lineHeight + contentsMarginsTop + contentsMarginsBottom; // Subtract lineHeight

    setMinimumHeight(height);
    setMaximumHeight(height);
    updateGeometry();

}*/
