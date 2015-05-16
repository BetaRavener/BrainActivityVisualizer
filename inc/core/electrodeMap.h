// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODE_MAP_H
#define ELECTRODE_MAP_H

#include <string>
#include <map>
#include <vector>

#include "electrode.h"
#include "electrodePlacer2D.h"
#include "electrodeLoader.h"

/**
 * @brief The ElectrodeMap class holds the electrodes and supports their importing and exporting.
 */
class ElectrodeMap
{
public:
    ElectrodeMap();

    /**
     * @brief Getter.
     * @param name Name of the electrode.
     * @return Pointer to the querried electrode.
     */
    Electrode::WeakPtr electrode(std::string name);

    /**
     * @brief Getter.
     * @return Pointers to all electrodes as a a vector.
     */
    std::vector<Electrode::WeakPtr> allElectrodes();

    /**
     * @brief Getter.
     * @return Names of all electrodes as a vector.
     */
    std::vector<std::string> allNames();

    /**
     * @brief Exports the current electrode map to a file.
     * @param path Path to the file.
     */
    void save(std::string path);

    /**
     * @brief Imorts new electrode map from a file.
     * @param path Path to the file.
     */
    void load(std::string path);

    /**
     * @brief Imports 3D positions to a current elecrode map from a file.
     * @param path Path to the file.
     */
    void import3D(std::string path);
private:
    std::map<std::string, Electrode::Ptr> _electrodeMap;

    std::string _header;
    unsigned int _version;
};

#endif
