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

    static Ptr create(edf_hdr_struct* header, int signalIdx);

    SignalData::Ptr load();
    std::string label() const;

private:
    SignalRecord();

    edf_hdr_struct* _header;
    int _signalIdx;
};

#endif
