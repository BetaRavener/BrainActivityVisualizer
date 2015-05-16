// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODE_LOADER_H
#define ELECTRODE_LOADER_H

#include <glm/common.hpp>
#include <string>
#include <map>

/**
 * @brief The ElectrodeLoader class loads the positions of electrodes from files.
 */
class ElectrodeLoader
{
public:
    /**
     * @brief Loads the electrode 3D positions from an obj file.
     * @param filename The path to the obj file.
     * @return Map of electrode names and positions.
     */
    static std::map<std::string, glm::vec3> load(std::string filename);
};

#endif
