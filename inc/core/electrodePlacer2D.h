// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODE_PLACER_2D_H
#define ELECTRODE_PLACER_2D_H

#include <glm/common.hpp>
#include <string>
#include <map>

/**
 * @brief The ElectrodePlacer2D class creates 2D electrode layouts.
 */
class ElectrodePlacer2D
{
public:
    /**
     * @brief Creates new 2D electrode layout according to standard
     * 10-10 placement system inspired by the figures in scientific papers.
     * @return A map of electrode names and 2D positions.
     */
    static std::map<std::string, glm::vec2> place();
};

#endif
