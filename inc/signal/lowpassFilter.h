#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "signalFilter.h"

class LowpassFilter : public SignalFilter
{
public:
    LowpassFilter(unsigned int halfLength, double cutoffFreq, double samplingFreq);
    virtual ~LowpassFilter();
};

#endif // LOWPASSFILTER_H
