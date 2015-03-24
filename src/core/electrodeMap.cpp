#include "electrodeMap.h"

std::string supportedElectrodes[] =
{
    "N1", "Nz", "N2",
    "Fp1", "Fpz", "Fp2",
    "AF9", "AF7", "AF5", "AF3", "AF1", "AFz", "AF2", "AF4", "AF6", "AF8", "AF10",
    "F9", "F7", "F5", "F3", "F1", "Fz", "F2", "F4", "F6", "F8", "F10",
    "FT9", "FT7", "FC5", "FC3", "FC1", "FCz", "FC2", "FC4", "FC6", "FT8", "FT10",
    "T9", "T7", "C5", "C3", "C1", "Cz", "C2", "C4", "C6", "T8", "T10",
    "TP9", "TP7", "CP5", "CP3", "CP1", "CPz", "CP2", "CP4", "CP6", "TP8", "TP10",
    "P9", "P7", "P5", "P3", "P1", "Pz", "P2", "P4", "P6", "P8", "P10",
    "PO9", "PO7", "PO5", "PO3", "PO1", "POz", "PO2", "PO4", "PO6", "PO8", "PO10",
    "O1", "Oz", "O2",
    "I1", "Iz", "I2"
};

ElectrodeMap::ElectrodeMap()
{
    auto elPos2D = ElectrodePlacer2D::place(50);
    auto elPos3D = ElectrodeLoader::load("electrodes/electrodes.obj");

    for (std::string elName : supportedElectrodes)
    {
        _electrodeMap.insert(std::pair<std::string, Electrode>(
                                 elName,
                                 Electrode(elName)));

        if (elPos2D.count(elName))
            _electrodeMap.at(elName).position2D(elPos2D[elName]);

        if (elPos3D.count(elName))
            _electrodeMap.at(elName).position3D(elPos3D[elName]);
    }
}

Electrode& ElectrodeMap::electrode(std::string name)
{
    return _electrodeMap.at(name);
}

const std::map<std::string, Electrode> &ElectrodeMap::allElectrodes()
{
    return _electrodeMap;
}

std::vector<std::string> ElectrodeMap::allNames()
{
    std::vector<std::string> names;
    for (std::string elName : supportedElectrodes)
        names.push_back(elName);

    return names;
}
