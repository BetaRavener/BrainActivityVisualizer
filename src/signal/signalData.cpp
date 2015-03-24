#include "signalData.h"

SignalData::Ptr SignalData::create()
{
    return Ptr(new SignalData);
}

SignalData::Ptr SignalData::create(unsigned int size)
{
    Ptr ptr(new SignalData);
    ptr->_data.resize(size);
    return ptr;
}

void SignalData::addSample(double sample)
{
    _data.push_back(sample);
}

unsigned int SignalData::sampleCount() const
{
    _data.size();
}

double SignalData::duration() const
{
    return _data.size() / _samplingFreq;
}

double SignalData::samplingFreq() const
{
    return _samplingFreq;
}

const std::vector<double> &SignalData::data() const
{
    return _data;
}

double *SignalData::writeAccess()
{
    return &_data[0];
}

SignalData::SignalData()
{

}
