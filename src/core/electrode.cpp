#include "electrode.h"

#define INACTIVE_COLOR glm::vec3(0.3, 0.3, 0.3)
#define UNAVAILBABLE_COLOR glm::vec3(0.5,0.0,0.5)
#define BASELINE_COLOR glm::vec3(0.0, 0.7, 0.0)
#define MAX_COLOR glm::vec3(1.0, 0.0, 0.0)
#define MIN_COLOR glm::vec3(0.0, 0.0, 1.0)

Electrode::Ptr Electrode::create(std::string name)
{
    Ptr ptr(new Electrode);
    ptr->_name = name;
    ptr->_has2D = false;
    ptr->_has3D = false;
    ptr->_position2D = glm::vec2(0,0);
    ptr->_position3D = glm::vec3(0,0,0);
    ptr->setInactive();
    return ptr;
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

glm::vec3 Electrode::color()
{
    return _color;
}

void Electrode::intensity(double intensity)
{
    _active = true;

    // Clamp to <-1, 1> interval
    intensity = glm::min(glm::max(intensity, -1.0), 1.0);

    // Convert intensity into color
    if (intensity >= 0.0)
    {
        _color = glm::mix(BASELINE_COLOR, MAX_COLOR, intensity);
    }
    else
    {
        _color = glm::mix(BASELINE_COLOR, MIN_COLOR, -intensity);
    }
}

void Electrode::setInactive()
{
    _active = false;
    _color = INACTIVE_COLOR;
}

void Electrode::setUnavailable()
{
    _color = UNAVAILBABLE_COLOR;
}

Electrode::Electrode()
{

}

