#ifndef BLACKMANWINDOW_H
#define BLACKMANWINDOW_H

#include "signalWindow.h"

class BlackmanWindow : public FilterWindow
{
public:
    BlackmanWindow(unsigned int length, double alfa = 0.16);
    virtual ~BlackmanWindow();
};

#endif // BLACKMANWINDOW_H
