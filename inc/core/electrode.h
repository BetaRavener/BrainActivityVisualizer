#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <glm/common.hpp>
#include <string>
#include "signalRecord.h"

class Electrode
{
public:
    Electrode(std::string name);

    const std::string& name();

    glm::vec2 position2D();
    glm::vec3 position3D();

    bool has2D();
    bool has3D();

    void position2D(glm::vec2 pos);
    void position3D(glm::vec3 pos);

    SignalRecord* signal();
    bool hasSignal();
    void signal(SignalRecord* signal);

private:
    std::string _name;

    bool _has2D;
    bool _has3D;

    glm::vec2 _position2D;
    glm::vec3 _position3D;

    SignalRecord* _signal;
};

#endif
