#ifndef ELECTRODE_PLACER_2D_H
#define ELECTRODE_PLACER_2D_H

#include <glm/common.hpp>
#include <string>
#include <map>

class ElectrodePlacer2D
{
public:
    static std::map<std::string, glm::vec2> place();
};

#endif
