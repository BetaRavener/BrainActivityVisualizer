#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include "signalBatch.h"

class InputModule
{
public:
    InputModule();
    InputModule(SignalBatch::Ptr signalBatch);
    ~InputModule();

    SignalBatch::WeakPtr signalBatch();

protected:
    SignalBatch::Ptr _signalBatch;
};

#endif // INPUTMODULE_H
