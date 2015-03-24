#include "dummyFilter.h"

#include <QEvent>

bool DummyFilter::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::Wheel)
    {
        return true;
    }

    return false;
}
