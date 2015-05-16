// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

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
