#include "signalBatch.h"
#include <algorithm>

SignalBatch::Ptr SignalBatch::create(std::vector<SignalData::Ptr> dataSignals)
{
    Ptr ptr(new SignalBatch());
    ptr->_signals = std::move(dataSignals);
    return ptr;
}

std::vector<SignalData::Ptr> SignalBatch::dataSignals()
{
    return _signals;
}

double SignalBatch::duration()
{
    double duration = 0.0;
    for (SignalData::Ptr data : _signals)
        duration = glm::max(duration, data->duration());

    return duration;
}

double SignalBatch::maxSamplingFreq()
{
    double samplingFreq = 0.0;
    for (SignalData::Ptr data : _signals)
        samplingFreq = glm::max(samplingFreq, data->samplingFreq());

    return samplingFreq;
}

double SignalBatch::maxResolution()
{
    return 1.0 / maxSamplingFreq();
}

void SignalBatch::clearElectrodeMappings()
{
    for (SignalData::WeakPtr signalData : _signals)
        signalData->clearElectrode();
}

SignalBatch::SignalBatch()
{

}
