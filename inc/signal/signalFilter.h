// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef SIGNALFILTER_H
#define SIGNALFILTER_H

#include "signalWindow.h"
#include "signalData.h"

/**
 * @brief The SignalFilter class is a base class for signal filters.s
 */
class SignalFilter
{
public:
    /**
     * @brief SignalFilter
     * @param halfLength Specifies the order of the filter. Order = 2 * halfLength.
     */
    SignalFilter(unsigned int halfLength);
    virtual ~SignalFilter();

    /**
     * @brief Filters the window producing one sample.
     * @param window Window to filter.
     * @return Resulting sample.
     */
    virtual double filter(const FilterWindow &window);

    /**
     * @brief Filters whole signal.
     * @param signal Signal to filter.
     * @param window Window to use for filtering.
     */
    void process(const SignalData::Ptr signal, FilterWindow &window);

protected:
    virtual double initialConditions(unsigned int idx, const SignalData::PtrConst signal);
    virtual double finalConditions(unsigned int idx, const SignalData::PtrConst signal);

    unsigned int _length;
    double* _impulseResponse;
};

#endif // SIGNALFILTER_H
