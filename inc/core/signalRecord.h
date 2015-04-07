#ifndef SIGNAL_RECORD_H
#define SIGNAL_RECORD_H

#include <string>
#include <vector>
#include <memory>
#include <safePtr.h>
#include <signalData.h>
#include "edflib.h"

class SignalRecord
{
public:
    typedef std::shared_ptr<SignalRecord> Ptr;
    typedef std::shared_ptr<const SignalRecord> PtrCost;
    typedef SafePtr<SignalRecord> WeakPtr;
    typedef SafePtr<const SignalRecord> WeakPtrConst;

    static Ptr create(int _signalFileHandle, int signalIdx, edf_param_struct* signalRecord, long long duration);

    SignalData::Ptr load();
    std::string label() const;

private:
    SignalRecord();

    int _signalFileHandle;
    int _signalIdx;
    edf_param_struct* _signalRecord;
    double _frequency;
};

#endif
