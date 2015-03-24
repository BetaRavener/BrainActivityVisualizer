#ifndef ELECTRODE_RENDERER_H
#define ELECTRODE_RENDERER_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeMap.h"

class ElectrodeRenderer
{
public:
    ElectrodeRenderer(ElectrodeMap* electrodeMap);
    virtual ~ElectrodeRenderer();

    virtual void init();

    void render();

    void reloadShaders();

protected:
    virtual void initializeShaders() = 0;

    ElectrodeMap* _electrodeMap;

    int _electrodeCount;

    // Buffers
    us::Buffer<float>::Ptr _electrodePosAttrBuf;

    us::UniShader* _renderEngine;
};

#endif
