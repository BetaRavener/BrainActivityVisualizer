#include "signalRecord.h"
#include "signalReader.h"

SignalRecord::SignalRecord(int signalFileHandle, int signalIdx, edf_param_struct* signalRecord) :
    _signalFileHandle(signalFileHandle),
    _signalIdx(signalIdx),
    _signalRecord(signalRecord)
{

}

SignalRecord::SignalRecord(const SignalRecord &other) :
    _signalRecord(other._signalRecord)
{

}

void SignalRecord::load()
{
    _signalData = SignalData::create(_signalRecord->smp_in_file);
    edfrewind(_signalFileHandle, _signalIdx);
    edfread_physical_samples(_signalFileHandle, _signalIdx, _signalRecord->smp_in_file, _signalData->writeAccess());
}

std::string SignalRecord::label() const
{
    return std::string(_signalRecord->label);
}

SignalData::PtrConst SignalRecord::data()
{
    return _signalData;
}
