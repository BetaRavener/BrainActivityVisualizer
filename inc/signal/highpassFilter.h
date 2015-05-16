// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef HIGHPASSFILTER_H
#define HIGHPASSFILTER_H

#include "signalFilter.h"

/**
 * @brief The HighpassFilter class represents a high pass filter.
 */
class HighpassFilter : public SignalFilter
{
public:
    HighpassFilter(unsigned int halfLength, double cutoffFreq, double samplingFreq);
    ~HighpassFilter();
};

#endif // HIGHPASSFILTER_H
