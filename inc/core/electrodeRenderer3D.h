#ifndef ELECTRODE_RENDERER_3D_H
#define ELECTRODE_RENDERER_3D_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeRenderer.h"

class ElectrodeRenderer3D : public ElectrodeRenderer
{
public:
    ElectrodeRenderer3D(std::vector<Electrode::WeakPtr> electrodes);

    void update(glm::vec3 eyePos, glm::mat4 mvpMatrix);

private:
    virtual void initializeShaders();
    virtual void prepareColorBuffer();

    // Attributes
    us::Attribute::Ptr _electrodePosAttr;

    // Uniforms
    us::Uniform::Ptr _radiusUnif;
    us::Uniform::Ptr _eyePosUnif;
    us::Uniform::Ptr _mvpMatrixUnif;
};

#endif
