#include "electrode.h"

Electrode::Electrode(std::string name) :
    _name(name),
    _has2D(false),
    _has3D(false),
    _position2D(glm::vec2(0,0)),
    _position3D(glm::vec3(0,0,0)),
    _signal(nullptr)
{
}

const std::string& Electrode::name()
{
    return _name;
}

glm::vec2 Electrode::position2D()
{
    return _position2D;
}

glm::vec3 Electrode::position3D()
{
    return _position3D;
}

bool Electrode::has2D()
{
    return _has2D;
}

bool Electrode::has3D()
{
    return _has3D;
}

void Electrode::position2D(glm::vec2 pos)
{
    _position2D = pos;
    _has2D = true;
}

void Electrode::position3D(glm::vec3 pos)
{
    _position3D = pos;
    _has3D = true;
}

SignalRecord *Electrode::signal()
{
    return _signal;
}

bool Electrode::hasSignal()
{
    return _signal != nullptr;
}

void Electrode::signal(SignalRecord *signal)
{
    _signal = signal;
}

