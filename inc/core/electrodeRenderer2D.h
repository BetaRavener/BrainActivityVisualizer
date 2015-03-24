#ifndef ELECTRODE_RENDERER_2D_H
#define ELECTRODE_RENDERER_2D_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeRenderer.h"

class ElectrodeRenderer2D : public ElectrodeRenderer
{
public:
    ElectrodeRenderer2D(ElectrodeMap* electrodeMap);

    void update(glm::mat4 mvpMatrix);

private:
    virtual void initializeShaders();

    // Attributes
    us::Attribute::Ptr _electrodePosAttr;

    // Uniforms
    us::Uniform::Ptr _radiusUnif;
    us::Uniform::Ptr _mvpMatrixUnif;
};

#endif
