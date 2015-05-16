// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef BLACKMANWINDOW_H
#define BLACKMANWINDOW_H

#include "signalWindow.h"

/**
 * @brief The BlackmanWindow class represents a blackman window used for filtering.
 */
class BlackmanWindow : public FilterWindow
{
public:
    BlackmanWindow(unsigned int length, double alfa = 0.16);
    virtual ~BlackmanWindow();
};

#endif // BLACKMANWINDOW_H
