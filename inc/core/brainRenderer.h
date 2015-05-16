// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef BRAIN_RENDERER_H
#define BRAIN_RENDERER_H

#include <vector>

#include <tiny_obj_loader.h>

#include <UniShader/UniShader.h>

#include <glm/common.hpp>

/**
 * @brief The BrainRenderer class provides methods for rendering brain using GPU.
 */
class BrainRenderer
{
public:
    BrainRenderer();
    /**
     * @brief Updates the brain renderer configuration.
     * @param eyePos New position of the camera.
     * @param mvpMatrix ModelViewProjection matrix that manipualtes 3D space.
     * @param modelMatrix Model matrix individually.
     */
    void update(glm::vec3 eyePos, glm::mat4 mvpMatrix, glm::mat4 modelMatrix);

    /**
     * @brief Renders the brain with actual settings.
     */
    void render();

    /**
     * @brief Reloads and reinitializes the shader program.
     */
    void reloadShaders();

    /**
     * @brief Initializes the renderer.
     */
    void init();
private:
    void initializeShaders();

    std::vector<tinyobj::shape_t> _shapes;
    std::vector<tinyobj::material_t> _materials;

    std::vector<unsigned int> _indicesCounts;

    // Buffers
    std::vector<us::Buffer<float>::Ptr> _posAttrBufs;
    std::vector<us::Buffer<float>::Ptr> _colAttrBufs;
    std::vector<us::Buffer<unsigned int>::Ptr> _indicesBufs;

    // Attributes
    us::Attribute::Ptr _posAttr;
    us::Attribute::Ptr _colAttr;

    // Uniforms
    us::Uniform::Ptr _eyePosUnif;
    us::Uniform::Ptr _lookAtUnif;
    us::Uniform::Ptr _matrixUnif;
    us::Uniform::Ptr _modelViewMatrixUnif;
    us::Uniform::Ptr _normalMatrixUnif;
    us::Uniform::Ptr _brainColorUnif;

    us::UniShader* _renderEngine;

    bool _brainLoaded;
    bool _initialized;
};

#endif
