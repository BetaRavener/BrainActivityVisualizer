// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef FILEINPUTMODULE_H
#define FILEINPUTMODULE_H

#include "inputModule.h"
#include "signalBatch.h"

/**
 * @brief The FileInputModule class represents data that are saved in a file.
 */
class FileInputModule : public InputModule
{
public:
    FileInputModule(SignalBatch::Ptr signalBatch);
    virtual ~FileInputModule();
};

#endif // FILEINPUTMODULE_H
