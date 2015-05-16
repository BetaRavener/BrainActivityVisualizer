// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "inputModule.h"

InputModule::InputModule() :
    _signalBatch(nullptr)
{

}

InputModule::InputModule(SignalBatch::Ptr signalBatch) :
    _signalBatch(signalBatch)
{

}

InputModule::~InputModule()
{

}

SignalBatch::WeakPtr InputModule::signalBatch()
{
    return _signalBatch;
}

