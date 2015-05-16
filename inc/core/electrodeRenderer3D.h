// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODE_RENDERER_3D_H
#define ELECTRODE_RENDERER_3D_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeRenderer.h"

/**
 * @brief The ElectrodeRenderer2D class is a specific class for rendering electrodes in 3D.
 */
class ElectrodeRenderer3D : public ElectrodeRenderer
{
public:
    ElectrodeRenderer3D();

    /**
     * @brief Updates the rendering configuration.
     * @param eyePos New camera position.
     * @param upDir Up vector of the camera.
     * @param rightDir Right vector of the camera.
     * @param mvpMatrix ModelViewProjection matrix.
     */
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
    us::Uniform::Ptr _eyePosUnif;
    us::Uniform::Ptr _mvpMatrixUnif;
};

#endif
