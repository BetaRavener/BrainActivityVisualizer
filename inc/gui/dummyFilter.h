// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef DUMMY_FILTER_H
#define DUMMY_FILTER_H

#include <QWidget>

/**
 * @brief The DummyFilter class overrides the eventFilter to nothing, so that it can be used for widgets
 * which should not be controlled directly by the user.
 */
class DummyFilter : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Empty event filter.
     */
    virtual bool eventFilter(QObject *, QEvent *event);
};

#endif
