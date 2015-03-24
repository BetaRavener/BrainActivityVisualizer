#ifndef DUMMY_FILTER_H
#define DUMMY_FILTER_H

#include <QWidget>

class DummyFilter : public QWidget
{
    Q_OBJECT

public:
    virtual bool eventFilter(QObject *, QEvent *event);
};

#endif
