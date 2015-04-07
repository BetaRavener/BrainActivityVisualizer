#ifndef SIGNAL_BATCH_H
#define SIGNAL_BATCH_H

#include <memory>
#include <vector>
#include "signalData.h"
#include "safePtr.h"

class SignalBatch
{
public:
    typedef std::shared_ptr<SignalBatch> Ptr;
    typedef std::shared_ptr<const SignalBatch> PtrConst;
    typedef SafePtr<SignalBatch> WeakPtr;
    typedef SafePtr<const SignalBatch> WeakPtrConst;

    static Ptr create(std::vector<SignalData::Ptr> dataSignals);
    std::vector<SignalData::Ptr> dataSignals();

    double duration();
    double maxSamplingFreq();
    double maxResolution();

    void clearElectrodeMappings();

private:
    SignalBatch();

    std::vector<SignalData::Ptr> _signals;
};

#endif
