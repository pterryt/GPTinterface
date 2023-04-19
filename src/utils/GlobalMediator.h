#ifndef GPTINTERFACE_GLOBALMEDIATOR_H
#define GPTINTERFACE_GLOBALMEDIATOR_H

#include <QObject>

class RightToolBar;
class BottomToolBar;
class WSTabWidget;

class GlobalMediator : public QObject
{
Q_OBJECT

public:

    static GlobalMediator* instance();
    static GlobalMediator* create();
    ~GlobalMediator() = default;
    GlobalMediator(const GlobalMediator &) = delete;
    GlobalMediator& operator=(const GlobalMediator &) = delete;

    GlobalMediator* setRightToolBar(RightToolBar* rtb);
    GlobalMediator* setBottomToolBar(BottomToolBar* btb);
    GlobalMediator* setWSTabWidget(WSTabWidget* wstw);

    RightToolBar* getRightToolBar();
    BottomToolBar* getBottomToolBar();
    WSTabWidget* getWSTabWidget();

    Q_SIGNALS:
    void sendInputTokenCount(int count);

public Q_SLOTS:

private:

    inline static GlobalMediator *m_mediator = nullptr;
    explicit GlobalMediator(QObject *parent = nullptr);

    RightToolBar *m_rightToolBar;
    BottomToolBar *m_bottomToolBar;
    WSTabWidget *m_tabWidget;



};

#endif // GPTINTERFACE_GLOBALMEDIATOR_H
