#ifndef HIGHPASSFILTER_H
#define HIGHPASSFILTER_H

#include "signalFilter.h"

class HighpassFilter : public SignalFilter
{
public:
    HighpassFilter(unsigned int halfLength, double cutoffFreq, double samplingFreq);
    ~HighpassFilter();
};

#endif // HIGHPASSFILTER_H
