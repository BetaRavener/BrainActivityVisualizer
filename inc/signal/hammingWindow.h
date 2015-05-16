// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef HAMMINGWINDOW_H
#define HAMMINGWINDOW_H

#include "signalWindow.h"

/**
 * @brief The BlackmanWindow class represents a hamming window used for filtering.
 */
class HammingWindow : public FilterWindow
{
public:
    HammingWindow(unsigned int length, double alfa = 0.54);
    virtual ~HammingWindow();
};

#endif // HAMMINGWINDOW_H
