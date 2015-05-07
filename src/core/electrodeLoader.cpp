#include "electrodeLoader.h"
#include <tiny_obj_loader.h>
#include <stdexcept>
#include <iostream>

std::map<std::string, glm::vec3> ElectrodeLoader::load(std::string filename)
{
    std::map<std::string, glm::vec3> electrodes;

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    // Load the 3d model from the file
    std::string err = tinyobj::LoadObj(shapes, materials, filename.c_str());

    if (!err.empty()) {
        throw std::runtime_error("Failed to load electrode file");
    }

    for (auto shape : shapes)
    {
        auto name = shape.name;
        glm::vec3 position;

        const std::vector<float>& positions = shape.mesh.positions;
        for (int i = 0; i < positions.size(); i += 3)
        {
            auto vertex = glm::vec3(positions[i], positions[i + 1], positions[i + 2]);
            position += vertex;
        }

        position /= (positions.size() / 3);
        electrodes[name] = position;
    }

    return electrodes;
}
