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

