#ifndef HAMMINGWINDOW_H
#define HAMMINGWINDOW_H

#include "signalWindow.h"

class HammingWindow : public FilterWindow
{
public:
    HammingWindow(unsigned int halfLength, double alfa = 0.54);
    virtual ~HammingWindow();
};

#endif // HAMMINGWINDOW_H
