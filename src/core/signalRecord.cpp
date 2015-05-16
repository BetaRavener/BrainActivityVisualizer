// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "signalRecord.h"
#include <algorithm>

SignalRecord::Ptr SignalRecord::create(edf_hdr_struct *header, int signalIdx)
{
    Ptr ptr(new SignalRecord);
    ptr->_header = header;
    ptr->_signalIdx = signalIdx;
    return ptr;
}

SignalData::Ptr SignalRecord::load()
{
    edf_param_struct& params = _header->signalparam[_signalIdx];
    long long samplesCount = params.smp_in_file;

    // Prepare storage
    std::vector<double> samples;
    samples.resize(samplesCount);

    // Prepare and read file
    edfrewind(_header->handle, _signalIdx);
    edfread_physical_samples(_header->handle, _signalIdx, samplesCount, &samples[0]);
    // Calculate this way to preserve resolution - the duration is in units of 100ns
    double freq = 1.e7 / (_header->datarecord_duration / params.smp_in_datarecord);
    SignalData::Ptr signalData =  SignalData::create(std::move(samples), freq, label());
    signalData->maxAmplitude(params.phys_max);
    signalData->minAmplitude(params.phys_min);
    return signalData;
}

std::string SignalRecord::label() const
{
    std::string label = std::string(_header->signalparam[_signalIdx].label);

    // Trim the string
    while(std::isspace(*label.rbegin()))
        label.erase(label.length()-1);

    return label;
}

SignalRecord::SignalRecord()
{
}
