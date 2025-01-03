#ifndef GPTINTERFACE_TOOLTIPEVENTFILTER_H
#define GPTINTERFACE_TOOLTIPEVENTFILTER_H
#define QT_NO_KEYWORDS
#include <QObject>

class ToolTipEventFilter : public QObject
{
Q_OBJECT

public:
    explicit ToolTipEventFilter(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // GPTINTERFACE_TOOLTIPEVENTFILTER_H
