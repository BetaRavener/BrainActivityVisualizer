// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <glm/common.hpp>

namespace glm{

/**
 * @brief The Helpers class is an extension to OpenGL mathematics library defining
 * usefull methods.
 */
class Helpers
{
public:
    /**
     * @brief Pushes a 2D point to an std::vector.
     * @param vector Vector where to push.
     * @param point The 2D point.
     */
    static void pushBack(std::vector<float>& vector, const glm::vec2& point);

    /**
     * @brief Pushes a 3D point to an std::vector.
     * @param vector Vector where to push.
     * @param point The 3D point.
     */
    static void pushBack(std::vector<float>& vector, const glm::vec3& point);

    /**
     * @brief Returns the next greater or equal (geq) power of 2 for the number.
     * @param num The number.
     * @return The next power of 2. Examples:
     * 5 -> 8
     * 16 -> 16
     * 1000 -> 1024
     */
    static int geqPow2(int num);
};

}

#endif // HELPERS_H
