#ifndef ELECTRODE_RENDERER_2D_H
#define ELECTRODE_RENDERER_2D_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeRenderer.h"

class ElectrodeRenderer2D : public ElectrodeRenderer
{
public:
    ElectrodeRenderer2D();

    void update(glm::vec3 eyePos, glm::vec3 upDir, glm::vec3 rightDir, glm::mat4 mvpMatrix);

private:
    virtual void initializeShaders();
    virtual void prepareColorBuffer();
    virtual void updateElectrodes();
    virtual bool electrodePresent(Electrode::WeakPtr electrode);

    // Attributes
    us::Attribute::Ptr _electrodePosAttr;

    // Uniforms
    us::Uniform::Ptr _radiusUnif;
    us::Uniform::Ptr _mvpMatrixUnif;

    float spacingRadius;
};

#endif
