#ifndef ELECTRODE_LOADER_H
#define ELECTRODE_LOADER_H

#include <glm/common.hpp>
#include <string>
#include <map>

class ElectrodeLoader
{
public:
    static std::map<std::string, glm::vec3> load(std::string filename);
};

#endif
