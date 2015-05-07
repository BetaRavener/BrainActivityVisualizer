#include "electrodePlacer2D.h"
#include <stdexcept>
#include <map>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "geometry.h"

std::map<std::string, glm::vec2> ElectrodePlacer2D::place()
{
    std::map<std::string, glm::vec2> electrodeMap;

    glm::vec2 placingVector(0.0f, 0.5f);

    // Place 2 most outer circles of electrodes
    float rotAngle = glm::pi<float>() / 10.0f;
    std::string names1[] = {"Nz", "N1", "AF9", "F9", "FT9", "T9", "TP9", "P9",
                            "PO9", "I1", "Iz", "I2", "PO10", "P10", "TP10", "T10",
                            "FT10", "F10", "AF10", "N2"};
    std::string names2[] = {"Fpz", "Fp1", "AF7", "F7", "FT7", "T7", "TP7", "P7",
                            "PO7", "O1", "Oz", "O2", "PO8", "P8", "TP8", "T8",
                            "FT8", "F8", "AF8", "Fp2"};
    for (int i = 0; i < 20; i++)
    {
        glm::vec2 rotVector = glm::rotate(placingVector, i * rotAngle);
        electrodeMap[names1[i]] = rotVector;
        electrodeMap[names2[i]] = rotVector * 0.8f;
    }

    // Form middle cross, duplicate Cz will be overwritten
    std::string names3[] = {"AFz", "Fz", "FCz", "Cz", "CPz", "Pz", "POz"};
    std::string names4[] = {"C5", "C3", "C1", "Cz", "C2", "C4", "C6"};
    for (int i = 0; i < 7; i++)
    {
        electrodeMap[names3[i]] = glm::vec2(0.0f, 0.3f - i * 0.1f);
        electrodeMap[names4[i]] = glm::vec2(-0.3f + i * 0.1f, 0.0f);
    }

    // Now place rest of the electrodes on circles made by circumscribing
    // triangles formed by already present electrodes (e.g. AF7 - AFz - AF8)
    // This time duplicates won't be overwritten
    // The first and last electrode name is used to determine placement vector
    // and is skipped
    std::string circumNames[][9] = {
        {"AF7", "AF5", "AF3", "AF1", "AFz", "AF2", "AF4", "AF6", "AF8"},
        {"F7", "F5", "F3", "F1", "Fz", "F2", "F4", "F6", "F8"},
        {"FT7", "FC5", "FC3", "FC1", "FCz", "FC2", "FC4", "FC6", "FT8"},
        {"TP7", "CP5", "CP3", "CP1", "CPz", "CP2", "CP4", "CP6", "TP8"},
        {"P7", "P5", "P3", "P1", "Pz", "P2", "P4", "P6", "P8"},
        {"PO7", "PO5", "PO3", "PO1", "POz", "PO2", "PO4", "PO6", "PO8"},
    };

    for (int i = 0; i < 6; i++)
    {
        glm::vec2 beginPos = electrodeMap[circumNames[i][0]];
        glm::vec2 middlePos = electrodeMap[circumNames[i][4]];
        glm::vec2 endPos = electrodeMap[circumNames[i][8]];
        geom2d::Circle circle = geom2d::Circle::circumscribeTriangle(geom2d::Triangle(
                                                    beginPos, middlePos, endPos));

        glm::vec2 beginVec = beginPos - circle.center();
        glm::vec2 endVec = endPos - circle.center();
        float angle = glm::angle(glm::normalize(beginVec), glm::normalize(endVec)) / 8.0f;

        if (i >= 3)
            angle *= -1.0f;

        for (int j = 1; j < 8; j++)
        {
            electrodeMap.insert(std::pair<std::string, glm::vec2>(
                                    circumNames[i][j],
                                    (circle.center() + glm::rotate(beginVec, j * angle))));
        }
    }

    return electrodeMap;
}

