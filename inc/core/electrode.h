#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <glm/common.hpp>
#include <string>
#include <memory>
#include "safePtr.h"

class Electrode
{
public:
    typedef std::shared_ptr<Electrode> Ptr;
    typedef std::shared_ptr<const Electrode> PtrConst;
    typedef SafePtr<Electrode> WeakPtr;
    typedef SafePtr<const Electrode> WeakPtrConst;

    static Ptr create(std::string name);

    const std::string& name();

    glm::vec2 position2D();
    glm::vec3 position3D();

    bool has2D();
    bool has3D();

    void position2D(glm::vec2 pos);
    void position3D(glm::vec3 pos);

    glm::vec3 color();
    void intensity(double intensity);
    void setInactive();
    void setUnavailable();

private:
    Electrode();

    std::string _name;

    bool _has2D;
    bool _has3D;

    glm::vec2 _position2D;
    glm::vec3 _position3D;

    glm::vec3 _color;
    bool _active;
};

#endif
