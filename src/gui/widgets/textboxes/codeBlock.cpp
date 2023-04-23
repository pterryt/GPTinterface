#include "codeBlock.h"
#include <QTextFrame>

codeBlock::codeBlock(QWidget *parent)
        : customTextEdit(parent)
{
    /* init syntax highlighter */
    m_syntaxHL = new QSourceHighlite::QSourceHighliter(m_doc);
    m_syntaxHL->setCurrentLanguage
            (QSourceHighlite::QSourceHighliter::CodeCpp);
    m_syntaxHL->setTheme(QSourceHighlite::QSourceHighliter::Themes::Monokai);

    /* setup page style */
    setStyleSheet("background-color: black;");
    QTextFrame *rootFrame = m_doc->rootFrame();
    QTextFrameFormat frameFormat = rootFrame->frameFormat();
    frameFormat.setLeftMargin(110.0);
    rootFrame->setFrameFormat(frameFormat);

    /* setup font */
    QFont font = QFont("JetBrains Mono");
    font.setPointSize(14);
    setFont(font);
}

/*
void codeBlock::appendText(const QString &text)
{
    customTextEdit::appendText(text);
    if (!text.contains('\n'))
    {
//        m_syntaxHL->rehighlightBlock(m_doc->lastBlock().previous());
    }
    updateSizeHint();
}*/
