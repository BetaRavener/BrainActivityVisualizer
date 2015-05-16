// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef SIGNAL_BATCH_H
#define SIGNAL_BATCH_H

#include <memory>
#include <vector>
#include "signalData.h"
#include "safePtr.h"

/**
 * @brief The SignalBatch class represents a group of signals.
 */
class SignalBatch
{
public:
    typedef std::shared_ptr<SignalBatch> Ptr;
    typedef std::shared_ptr<const SignalBatch> PtrConst;
    typedef SafePtr<SignalBatch> WeakPtr;
    typedef SafePtr<const SignalBatch> WeakPtrConst;

    /**
     * @brief Groups the signals into batch.
     * @param dataSignals Signals to group.
     * @return Signal batch.
     */
    static Ptr create(std::vector<SignalData::Ptr> dataSignals);
    std::vector<SignalData::Ptr> dataSignals();

    /**
     * @brief Getter.
     * @return The duration of the batch determined by the longest signal in group.
     */
    double duration();

    /**
     * @brief Getter.
     * @return The sampling frequency of the signal in group with maximum sampling frequency.
     */
    double maxSamplingFreq();

    /**
     * @brief Getter.
     * @return The time resolution of the signal in group with maximum resolution.
     */
    double maxResolution();

    /**
     * @brief Clear the electrode mapping for all signals in this group.
     */
    void clearElectrodeMappings();

private:
    SignalBatch();

    std::vector<SignalData::Ptr> _signals;
};

#endif
