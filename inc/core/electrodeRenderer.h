#ifndef ELECTRODE_RENDERER_H
#define ELECTRODE_RENDERER_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeMap.h"

class ElectrodeRenderer
{
public:
    ElectrodeRenderer(std::vector<Electrode::WeakPtr> electrodes);
    virtual ~ElectrodeRenderer();

    virtual void init();

    void render();

    void reloadShaders();

protected:
    virtual void initializeShaders() = 0;
    virtual void prepareColorBuffer() = 0;

    std::vector<Electrode::WeakPtr> _electrodes;

    int _electrodeCount;

    // Buffers
    us::Buffer<float>::Ptr _electrodePosAttrBuf;
    us::Buffer<float>::Ptr _electrodeColorAttrBuf;

    // Attributes
    us::Attribute::Ptr _electrodeColorAttr;

    us::UniShader* _renderEngine;
};

#endif
