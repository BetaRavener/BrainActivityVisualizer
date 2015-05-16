// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "signalFilter.h"
#include <utility>

SignalFilter::SignalFilter(unsigned int halfLength) :
    _length(2 * halfLength + 1),
    _impulseResponse(nullptr)
{
    _impulseResponse = new double[_length];
    for (unsigned int i = 0; i < _length; i++)
        _impulseResponse[i] = 0.0;
}

SignalFilter::~SignalFilter()
{
    delete[] _impulseResponse;
}

double SignalFilter::filter(const FilterWindow &window)
{
    double convolutedSample = 0.0;
    for (unsigned int i = 0, j = _length - 1; i < _length; i++, j--)
    {
        convolutedSample += window[i] * _impulseResponse[j];
    }

    return convolutedSample;
}

void SignalFilter::process(const SignalData::Ptr signal, FilterWindow &window)
{
    const auto& data = signal->data();
    unsigned int count = signal->sampleCount();

    SignalData::Samples result;

    if (count == 0)
    {
        signal->data(std::move(result));
        return;
    }

    window.clear();
    result.reserve(count);

    for (unsigned int i = 0; i < window.length() - 1; i++)
        window.addSample(initialConditions(i, signal));

    for (unsigned int i = 0; i < count; i++)
    {
        window.addSample(data[i]);
        result.push_back(filter(window));
    }

    signal->data(std::move(result));
}

double SignalFilter::initialConditions(unsigned int idx, const SignalData::PtrConst signal)
{
    return 0.0;
}

double SignalFilter::finalConditions(unsigned int idx, const SignalData::PtrConst signal)
{
    return 0.0;
}

