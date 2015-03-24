#ifndef ELECTRODE_MAP_H
#define ELECTRODE_MAP_H

#include <string>
#include <map>
#include <vector>

#include "electrode.h"
#include "electrodePlacer2D.h"
#include "electrodeLoader.h"

class ElectrodeMap
{
public:
    ElectrodeMap();

    Electrode& electrode(std::string name);
    const std::map<std::string, Electrode>& allElectrodes();
    static std::vector<std::string> allNames();
private:

    std::map<std::string, Electrode> _electrodeMap;
};

#endif
