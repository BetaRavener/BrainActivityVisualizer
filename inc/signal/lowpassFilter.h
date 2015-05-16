// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "signalFilter.h"

/**
 * @brief The LowpassFilter class represents a lowpass filter.
 */
class LowpassFilter : public SignalFilter
{
public:
    LowpassFilter(unsigned int halfLength, double cutoffFreq, double samplingFreq);
    virtual ~LowpassFilter();
};

#endif // LOWPASSFILTER_H
