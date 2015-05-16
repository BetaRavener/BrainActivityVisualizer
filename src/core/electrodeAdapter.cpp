// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "electrodeAdapter.h"
#include <cmath>

#include "fourierTransform.h"

ElectrodeAdapter::ElectrodeAdapter() :
    _gain(100.0),
    _transformationType(TransformationType::None)
{

}

ElectrodeAdapter::~ElectrodeAdapter()
{

}

void ElectrodeAdapter::init(SignalBatch::WeakPtr batch)
{
    _signalBatch = batch;
}

void ElectrodeAdapter::setTime(double time)
{
    if (_signalBatch)
    {
        switch(_transformationType)
        {
        case TransformationType::None:
            noTransformation(time);
            break;
        case TransformationType::FFT:
            fftTransformation(time);
            break;
        }
    }
}

double ElectrodeAdapter::gain()
{
    return _gain;
}

void ElectrodeAdapter::gain(double gain)
{
    _gain = gain;
}

ElectrodeAdapter::TransformationType ElectrodeAdapter::transformationType()
{
    return _transformationType;
}

void ElectrodeAdapter::transformationType(ElectrodeAdapter::TransformationType type)
{
    _transformationType = type;
}

double ElectrodeAdapter::transformationBeginFreq()
{
    return _transformationBeginFreq;
}

void ElectrodeAdapter::transformationBeginFreq(double freq)
{
    _transformationBeginFreq = freq;
}

double ElectrodeAdapter::transformationEndFreq()
{
    return _transformationEndFreq;
}

void ElectrodeAdapter::transformationEndFreq(double freq)
{
    _transformationEndFreq = freq;
}

void ElectrodeAdapter::noTransformation(double time)
{
    for (SignalData::WeakPtr signalData : _signalBatch->dataSignals())
    {
        if (signalData->electrode())
        {
            signalData->electrode()->intensity(signalData->getSampleAtTime(time, true) * _gain);
        }
    }
}

void ElectrodeAdapter::fftTransformation(double time, double resolution)
{
    for (SignalData::WeakPtr signalData : _signalBatch->dataSignals())
    {
        if (signalData->electrode())
        {
            unsigned int samples = signalData->samplingFreq() / resolution;
            unsigned int idx = signalData->getIdxAtTime(time);

            if (idx < samples / 2 || idx + samples / 2 >= signalData->sampleCount())
            {
                signalData->electrode()->setUnavailable();
                continue;
            }

            idx -= samples / 2;

            FourierTransform transform;
            transform.init(samples);

            try
            {
                Spectrum::Ptr spectrum = transform.process(signalData, idx);
                double intensity = spectrum->max(_transformationBeginFreq, _transformationEndFreq);
                intensity = spectrum->normalize(intensity);
                signalData->electrode()->intensity(intensity * _gain);
            }
            catch (std::exception e)
            {
                signalData->electrode()->setUnavailable();
            }
        }
    }
}

