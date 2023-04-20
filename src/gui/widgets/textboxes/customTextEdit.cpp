#include "customTextEdit.h"
#include <QShortcut>
#include <iostream>
#include "../RightToolBar.h"
#include <QTextBlock>


customTextEdit::customTextEdit(QWidget *parent)
        : QTextEdit(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setStyleSheet("padding: 0px; margin: 0px;");
//    setLineWrapMode(WidgetWidth);
    setLineWrapMode(NoWrap);
    setReadOnly(true);
    QTextDocument *doc = document();
    doc->setDocumentMargin(0);
    m_appendCursor = new QTextCursor(document());
}


void customTextEdit::appendText(const QString &text)
{
    m_appendCursor->movePosition(QTextCursor::End);
    m_appendCursor->insertText(text);
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


