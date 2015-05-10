#ifndef ELECTRODE_RENDERER_H
#define ELECTRODE_RENDERER_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeMap.h"

class ElectrodeRenderer
{
public:
    ElectrodeRenderer();
    virtual ~ElectrodeRenderer();

    virtual void init();

    void render();

    virtual void update(glm::vec3 eyePos, glm::vec3 upDir, glm::vec3 rightDir, glm::mat4 mvpMatrix);

    void electrodes(std::vector<Electrode::WeakPtr> electrodes);

    void reloadShaders();

protected:
    virtual void initializeShaders();
    virtual void prepareColorBuffer() = 0;
    virtual void updateElectrodes() = 0;
    virtual bool electrodePresent(Electrode::WeakPtr) = 0;

    void prepareNamesTexture();

    std::vector<Electrode::WeakPtr> _electrodes;

    int _electrodeCount;

    // Buffers
    us::Buffer<float>::Ptr _electrodePosAttrBuf;
    us::Buffer<float>::Ptr _electrodeColorAttrBuf;

    us::Buffer<float>::Ptr _namesBottomLeftUVAttrBuf;
    us::Buffer<float>::Ptr _namesTopRightUVAttrBuf;

    // Attributes
    us::Attribute::Ptr _electrodeColorAttr;

    us::Attribute::Ptr _namesPosAttr;
    us::Attribute::Ptr _namesBottomLeftUVAttr;
    us::Attribute::Ptr _namesTopRightUVAttr;

    // Uniforms
    us::Uniform::Ptr _namesUpDirUnif;
    us::Uniform::Ptr _namesEyePosUnif;
    us::Uniform::Ptr _namesRightDirUnif;
    us::Uniform::Ptr _namesTextureUnif;
    us::Uniform::Ptr _namesMvpMatrixUnif;
    us::Uniform::Ptr _namesTextureAspectUnif;

    us::UniShader* _renderEngine;
    us::UniShader* _namesEngine;

    bool _electrodesChanged;
};

#endif
