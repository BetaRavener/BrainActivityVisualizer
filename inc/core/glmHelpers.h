#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <glm/common.hpp>

namespace glm{

class Helpers
{
public:
    static void pushBack(std::vector<float>& vector, const glm::vec2& point);
    static void pushBack(std::vector<float>& vector, const glm::vec3& point);
};

}

#endif // HELPERS_H
