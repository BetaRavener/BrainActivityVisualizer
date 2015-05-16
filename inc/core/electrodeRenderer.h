// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODE_RENDERER_H
#define ELECTRODE_RENDERER_H

#include <vector>

#include <UniShader/UniShader.h>

#include "electrodeMap.h"

/**
 * @brief The ElectrodeRenderer class is a base class for electrode renderers.
 */
class ElectrodeRenderer
{
public:
    ElectrodeRenderer();
    virtual ~ElectrodeRenderer();

    /**
     * @brief Initializes the class before usage.
     */
    virtual void init();

    /**
     * @brief Renders the electrodes.
     */
    void render();

    /**
     * @brief Updates the rendering configuration.
     * @param eyePos New camera position.
     * @param upDir Up vector of the camera.
     * @param rightDir Right vector of the camera.
     * @param mvpMatrix ModelViewProjection matrix.
     */
    virtual void update(glm::vec3 eyePos, glm::vec3 upDir, glm::vec3 rightDir, glm::mat4 mvpMatrix);

    /**
     * @brief Assigns electrodes to the renderer.
     * @param electrodes
     */
    void electrodes(std::vector<Electrode::WeakPtr> electrodes);

    /**
     * @brief Reloads and reinitializes the shader programs.
     */
    void reloadShaders();

    /**
     * @brief Setter.
     * @param show If true, the names of the electrodes will be rendered.
     */
    void showNames(bool show);

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
    bool _showNames;
};

#endif
