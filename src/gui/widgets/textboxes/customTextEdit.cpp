#include "customTextEdit.h"

#include <QShortcut>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QDir>

#include "../RightToolBar.h"


customTextEdit::customTextEdit(const int wsIndex, QWidget *parent)
        : QTextEdit(parent), parentWSIndex(wsIndex)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setLineWrapMode(WidgetWidth);
    setContentsMargins(0,0,0,0);
    setReadOnly(true);
    updateSizeHint();
    m_appendCursor = new QTextCursor(document());

    QString dirname =
            "audio_clips/ws_" + QString::number(wsIndex) + "cte_" + QString::number(convoIndex);
    QDir dir;

    if (!dir.exists(dirname))
    {
        dir.mkdir(dirname);
    }

}

void customTextEdit::appendText(const QString &text)
{
    m_appendCursor->movePosition(QTextCursor::End);
    m_appendCursor->insertText(text);
    updateSizeHint();
}

void customTextEdit::updateSizeHint()
{

    int viewportWidth = viewport()->width();
    document()->setTextWidth(viewportWidth);

    int contentsMarginsTop = contentsMargins().top();
    int contentsMarginsBottom = contentsMargins().bottom();

    int height = document()->size().height() + contentsMarginsBottom +
            contentsMarginsTop;

    setMinimumHeight(height);
    setMaximumHeight(height);
    updateGeometry();

    if (parentWidget())
    {
        parentWidget()->updateGeometry();
    }
}

void customTextEdit::removeTrailingBlankLines()
{
    m_appendCursor->movePosition(QTextCursor::End);

    while (!m_appendCursor->atStart())
    {
        m_appendCursor->movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);

        QString currentLine = m_appendCursor->block().text();
        if (!currentLine.isEmpty())
        {
            break;
        }

        m_appendCursor->movePosition(QTextCursor::EndOfBlock,
                                     QTextCursor::MoveAnchor);
        m_appendCursor->movePosition(QTextCursor::EndOfBlock,
                                     QTextCursor::KeepAnchor);
        m_appendCursor->removeSelectedText();
        m_appendCursor->deletePreviousChar();
        updateSizeHint();
    }
}

int customTextEdit::getParentWsIndex() const
{
    return parentWSIndex;
}

customTextEdit::bType customTextEdit::getBtype() const
{
    return btype;
}


