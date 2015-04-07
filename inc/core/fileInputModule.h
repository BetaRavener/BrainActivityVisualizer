#ifndef FILEINPUTMODULE_H
#define FILEINPUTMODULE_H

#include "inputModule.h"
#include "signalBatch.h"

class FileInputModule : public InputModule
{
public:
    FileInputModule(SignalBatch::Ptr signalBatch);
    virtual ~FileInputModule();
};

#endif // FILEINPUTMODULE_H
