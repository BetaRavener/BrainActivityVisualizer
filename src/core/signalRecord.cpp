#include "signalRecord.h"
#include <algorithm>

SignalRecord::Ptr SignalRecord::create(int _signalFileHandle, int signalIdx, edf_param_struct *signalRecord, long long duration)
{
    Ptr ptr(new SignalRecord);
    ptr->_signalFileHandle = _signalFileHandle;
    ptr->_signalIdx = signalIdx;
    ptr->_signalRecord = signalRecord;
    // Calculate this way to preserve resolution - the duration is in units of 100ns
    ptr->_frequency = 1.e7 / (duration / signalRecord->smp_in_file);
    return ptr;
}

SignalData::Ptr SignalRecord::load()
{
    // Prepare storage
    std::vector<double> samples;
    samples.resize(_signalRecord->smp_in_file);

    // Prepare and read file
    edfrewind(_signalFileHandle, _signalIdx);
    edfread_physical_samples(_signalFileHandle, _signalIdx, _signalRecord->smp_in_file, &samples[0]);
    SignalData::Ptr signalData =  SignalData::create(std::move(samples), _frequency, label());
    signalData->maxAmplitude(_signalRecord->phys_max);
    signalData->minAmplitude(_signalRecord->phys_min);
    return signalData;
}

std::string SignalRecord::label() const
{
    std::string label = std::string(_signalRecord->label);

    // Trim the string
    while(std::isspace(*label.rbegin()))
        label.erase(label.length()-1);

    return label;
}

SignalRecord::SignalRecord()
{
}
