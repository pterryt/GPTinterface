#ifndef SCROLLTEST_H
#define SCROLLTEST_H

#define QT_NO_KEYWORDS
#include <QTextEdit>

class customTextEdit : public QTextEdit
{
    Q_OBJECT

public:

    explicit customTextEdit(int wsIndex, QWidget *parent = nullptr);

    /**
    * Cursor used for appendText. Used by the workspace as well for removing
     * text.
    */
    QTextCursor *m_appendCursor;

    /**
    * Removes blank lines at the end of the text edit. Calls updateSizeHint
     * after.
    */

    void removeTrailingBlankLines();

    QMap<QString,QUrl> *convoStorage;
    /**
    * Index on customScrollArea. Used by PollyUtility to insert into correct convoStorage Map.
    */
    int convoIndex = 0;

public Q_SLOTS:

    /**
    * Append text to the end of the document regardless of where the users
     * cursor is.
    */
    void appendText(const QString &text);

    /**
    * Resize the text edit based on the size of the document and it's margins.
    */
    void updateSizeHint();

private:

    int parentWSIndex;
public:
    int getParentWsIndex() const;
};

#endif // SCROLLTEST_H
