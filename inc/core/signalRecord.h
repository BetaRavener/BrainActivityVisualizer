// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef SIGNAL_RECORD_H
#define SIGNAL_RECORD_H

#include <string>
#include <vector>
#include <memory>
#include <safePtr.h>
#include <signalData.h>
#include "edflib.h"

/**
 * @brief The SignalRecord class represents a single signal record in EDF file.
 */
class SignalRecord
{
public:
    typedef std::shared_ptr<SignalRecord> Ptr;
    typedef std::shared_ptr<const SignalRecord> PtrCost;
    typedef SafePtr<SignalRecord> WeakPtr;
    typedef SafePtr<const SignalRecord> WeakPtrConst;

    /**
     * @brief Creates new signal record.
     * @param header EDFlib file header.
     * @param signalIdx Index of signal to create.
     * @return The created signal record.
     */
    static Ptr create(edf_hdr_struct* header, int signalIdx);

    /**
     * @brief Actually loads the data associated with the signal record.
     * @return The signal data - samples.
     */
    SignalData::Ptr load();

    /**
     * @brief Getter.
     * @return Label of the record in EDF file.
     */
    std::string label() const;

private:
    SignalRecord();

    edf_hdr_struct* _header;
    int _signalIdx;
};

#endif
