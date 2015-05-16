// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "signalData.h"
#include <algorithm>

SignalData::Ptr SignalData::create()
{
    return Ptr(new SignalData);
}

SignalData::Ptr SignalData::create(Samples samples, double freq, std::string label, Electrode::WeakPtr electrode)
{
    Ptr ptr(new SignalData);
    ptr->_data = std::move(samples);
    ptr->_samplingFreq = freq;
    ptr->_label = label;
    ptr->_electrode = electrode;
    return ptr;
}

void SignalData::addSample(double sample)
{
    _data.push_back(sample);
}

double SignalData::getSampleAtTime(double time, bool normalize) const
{
    double sample =  _data[getIdxAtTime(time)];

    if (normalize)
        sample = normalizeSample(sample);

    return sample;
}

unsigned int SignalData::getIdxAtTime(double time) const
{
    return glm::min((unsigned int)(time * _samplingFreq), _data.size() - 1);
}

double SignalData::normalizeSample(double sample) const
{
    double range = _maxAmplitude - _minAmplitude;
    double baseLine = 0.5;

    double normalizedSample = ((sample - _minAmplitude) / range) - baseLine;
    if (normalizedSample >= 0.0)
    {
        normalizedSample /= 1.0 - baseLine;
    }
    else
    {
        normalizedSample /= baseLine;
    }

    normalizedSample = glm::min(glm::max(normalizedSample, -1.0), 1.0);
    return normalizedSample;
}

unsigned int SignalData::sampleCount() const
{
    return _data.size();
}

double SignalData::duration() const
{
    return _data.size() / _samplingFreq;
}

double SignalData::samplingFreq() const
{
    return _samplingFreq;
}

const SignalData::Samples &SignalData::data() const
{
    return _data;
}

void SignalData::data(SignalData::Samples samples)
{
    _data = std::move(samples);
}

std::string SignalData::label() const
{
    return _label;
}

void SignalData::label(std::string label)
{
    _label = label;
}

Electrode::WeakPtr SignalData::electrode() const
{
    return _electrode;
}

void SignalData::electrode(Electrode::WeakPtr electrode)
{
    _electrode = electrode;
}

void SignalData::clearElectrode()
{
    _electrode = Electrode::WeakPtr();
}

double SignalData::minAmplitude() const
{
    return _minAmplitude;
}

void SignalData::minAmplitude(double amp)
{
    _minAmplitude = amp;
}

double SignalData::maxAmplitude() const
{
    return _maxAmplitude;
}

void SignalData::maxAmplitude(double amp)
{
    _maxAmplitude = amp;
}

SignalData::SignalData()
{

}
