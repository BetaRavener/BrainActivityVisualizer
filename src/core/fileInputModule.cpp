// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "fileInputModule.h"

#include <utility>

FileInputModule::FileInputModule(SignalBatch::Ptr signalBatch) :
    InputModule(signalBatch)
{

}

FileInputModule::~FileInputModule()
{
}
