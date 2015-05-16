// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include "signalBatch.h"

/**
 * @brief The InputModule class represents EEG data source.
 */
class InputModule
{
public:
    InputModule();
    InputModule(SignalBatch::Ptr signalBatch);
    ~InputModule();

    /**
     * @brief Getter.
     * @return Group of signals stored by the module.
     */
    SignalBatch::WeakPtr signalBatch();

protected:
    SignalBatch::Ptr _signalBatch;
};

#endif // INPUTMODULE_H
