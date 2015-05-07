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

    Electrode::WeakPtr electrode(std::string name);
    std::vector<Electrode::WeakPtr> allElectrodes();
    std::vector<std::string> allNames();

    void save(std::string path);
    void load(std::string path);

    void import3D(std::string path);
private:
    std::map<std::string, Electrode::Ptr> _electrodeMap;

    std::string _header;
    unsigned int _version;
};

#endif
