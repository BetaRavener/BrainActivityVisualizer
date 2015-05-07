#include "glmHelpers.h"

void glm::Helpers::pushBack(std::vector<float> &vector, const glm::vec2 &point)
{
    vector.push_back(point.x);
    vector.push_back(point.y);
}

void glm::Helpers::pushBack(std::vector<float> &vector, const glm::vec3 &point)
{
    vector.push_back(point.x);
    vector.push_back(point.y);
    vector.push_back(point.z);
}

int glm::Helpers::geqPow2(int num)
{
    if (num <= 0)
        return 0;

    int pow2 = 1;
    while (pow2 < num)
        pow2 <<= 1;

    return pow2;
}
