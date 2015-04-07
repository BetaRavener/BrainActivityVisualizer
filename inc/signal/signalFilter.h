#ifndef SIGNALFILTER_H
#define SIGNALFILTER_H

#include "signalWindow.h"
#include "signalData.h"

class SignalFilter
{
public:
    SignalFilter(unsigned int halfLength);
    virtual ~SignalFilter();

    virtual double filter(const FilterWindow &window);
    void process(const SignalData::Ptr signal, FilterWindow &window);

protected:
    virtual double initialConditions(unsigned int idx, const SignalData::PtrConst signal);
    virtual double finalConditions(unsigned int idx, const SignalData::PtrConst signal);

    unsigned int _length;
    double* _impulseResponse;
};

#endif // SIGNALFILTER_H
