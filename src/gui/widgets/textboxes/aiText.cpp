#include "aiText.h"
#include <QTextFrame>

aiText::aiText(const int wsIndex, QWidget *parent)
        : customTextEdit(wsIndex, parent)
{
    setStyleSheet("background-color: black;");

    /* setup page style */
    QTextFrame *rootFrame = m_doc->rootFrame();
    QTextFrameFormat frameFormat = rootFrame->frameFormat();
    frameFormat.setMargin(10.0);
    frameFormat.setLeftMargin(60.0);
    rootFrame->setFrameFormat(frameFormat);

    /* setup font */
    QFont font = QFont("SansSerif");
    font.setPointSize(14);
    setFont(font);
    btype = AI;
    qDebug() << "aiText made with btype: " << btype;

}
