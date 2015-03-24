#ifndef SIGNAL_RECORD_H
#define SIGNAL_RECORD_H

#include <string>
#include <vector>
#include <signalData.h>
#include "edflib.h"

class SignalReader;

class SignalRecord
{
public:
    SignalRecord(int _signalFileHandle, int signalIdx, edf_param_struct* signalRecord);

    void load();

    std::string label() const;
    SignalData::PtrConst data();
private:
    // Disable copy constructor
    SignalRecord(const SignalRecord& other);

    int _signalFileHandle;
    int _signalIdx;
    edf_param_struct* _signalRecord;
    SignalData::Ptr _signalData;
};

#endif
