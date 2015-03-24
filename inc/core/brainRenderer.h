#ifndef BRAIN_RENDERER_H
#define BRAIN_RENDERER_H

#include <vector>

#include <tiny_obj_loader.h>

#include <UniShader/UniShader.h>

#include <glm/common.hpp>

class BrainRenderer
{
public:
    BrainRenderer();
    void update(glm::vec3 eyePos, glm::mat4 mvpMatrix, glm::mat4 modelMatrix);
    void render();

    void reloadShaders();

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
};

#endif
