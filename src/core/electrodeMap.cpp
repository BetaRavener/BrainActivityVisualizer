#include "electrodeMap.h"
#include <fstream>
#include <stdexcept>
#include <utility>

#define SKIP_MARK "*"

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

ElectrodeMap::ElectrodeMap() :
    _header("Electrode map file v"),
    _version(100)
{
    bool defPlacement = false;
    try
    {
        load("electrodes/default.elmap");
        defPlacement = true;
    }
    catch(std::exception e)
    {
    }

    if (!defPlacement)
    {
        auto elPos2D = ElectrodePlacer2D::place();
        for (std::string elName : supportedElectrodes)
        {
            _electrodeMap.insert(std::pair<std::string, Electrode::Ptr>(
                                     elName,
                                     Electrode::create(elName)));

            if (elPos2D.count(elName))
                _electrodeMap.at(elName)->position2D(elPos2D[elName]);
        }
    }
}

Electrode::WeakPtr ElectrodeMap::electrode(std::string name)
{
    if (_electrodeMap.count(name))
        return Electrode::WeakPtr(_electrodeMap.at(name));
    else
        return Electrode::WeakPtr();
}

std::vector<Electrode::WeakPtr> ElectrodeMap::allElectrodes()
{
    std::vector<Electrode::WeakPtr> ret;

    for (auto pair : _electrodeMap)
    {
        ret.push_back(Electrode::WeakPtr(pair.second));
    }

    return ret;
}

std::vector<std::string> ElectrodeMap::allNames()
{
    std::vector<std::string> names;
    for (auto& pair : _electrodeMap)
        names.push_back(pair.first);

    return names;
}

void ElectrodeMap::save(std::string path)
{
    std::ofstream fout;

    fout.open(path);
    if (fout.is_open())
    {
        fout << _header << _version << std::endl;
        for (auto& pair : _electrodeMap)
        {
            std::string elName = pair.first;
            Electrode::WeakPtr electrode = pair.second;
            fout << elName;
            if (electrode->has2D())
            {
                glm::vec2 pos = electrode->position2D();
                fout << " " << pos.x << " " << pos.y;
            }
            else
            {
                fout << " " << SKIP_MARK;
            }
            if (electrode->has3D())
            {
                glm::vec3 pos = electrode->position3D();
                fout << " " << pos.x << " " << pos.y << " " << pos.z;
            }
            else
            {
                fout << " " << SKIP_MARK;
            }
            fout << std::endl;
        }
    }
    else
        throw std::runtime_error("Failed to open file");
}

void ElectrodeMap::load(std::string path)
{
    std::ifstream fin;

    fin.open(path);
    if (fin.is_open())
    {
        std::map<std::string, Electrode::Ptr> newMap;

        std::string tmp;
        std::getline(fin, tmp);

        if (_header.compare(tmp.substr(0, _header.size())) != 0)
        {
            throw std::runtime_error("File is not electrode map file");
        }

        if (std::stoul(tmp.substr(_header.size())) != _version)
        {
            throw std::runtime_error("Different version of electrode map file");
        }

        while (true)
        {
            std::string elName;
            double vals[3];

            if (fin >> tmp)
                elName = tmp;
            else
                break;

            Electrode::Ptr electrode = Electrode::create(elName);

            try
            {
                int i;
                for (i = 0; i < 2 && fin >> tmp; i++)
                {
                    if (tmp == SKIP_MARK)
                        break;

                    vals[i] = std::stod(tmp);
                }

                if (i == 2)
                    electrode->position2D(glm::vec2(vals[0], vals[1]));
                else if (!(i == 0 && tmp == SKIP_MARK))
                    throw std::runtime_error("Incorrect record");

                for (i = 0; i < 3 && fin >> tmp; i++)
                {
                    if (tmp == SKIP_MARK)
                        break;

                    vals[i] = std::stod(tmp);
                }

                if (i == 3)
                    electrode->position3D(glm::vec3(vals[0], vals[1], vals[2]));
                else if (!(i == 0 && tmp == SKIP_MARK))
                    throw std::runtime_error("Incorrect record");
            }
            catch (std::exception e)
            {
                throw std::runtime_error("Corrupted file");
            }

            // Test if record already exists
            if (newMap.count(elName))
                throw std::runtime_error("Corrupted file");

            newMap.insert(std::pair<std::string, Electrode::Ptr>(
                                     elName,
                                     electrode));
        }

        _electrodeMap = std::move(newMap);
    }
    else
        throw std::runtime_error("Failed to open file");
}

void ElectrodeMap::import3D(std::string path)
{
    auto elPos3D = ElectrodeLoader::load(path);
    for (auto& electrodePair : _electrodeMap)
    {
        if (elPos3D.count(electrodePair.first))
            electrodePair.second->position3D(elPos3D[electrodePair.first]);
    }
}
