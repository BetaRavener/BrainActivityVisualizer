#ifndef GRAPH_GRID_2D_H
#define GRAPH_GRID_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>

class ShapeRenderer2D
{
public:
    ShapeRenderer2D();
    ~ShapeRenderer2D();

    void init();

    void update(glm::mat4 mvpMatrix);

    void render(us::PrimitiveType type, unsigned int count);

    void setPositions(const std::vector<float>& positions);
    void setColors(const std::vector<float>& colors);

    void reloadShaders();

private:
    void initializeShaders();

    unsigned int _valueCount;

    // Buffers
    us::Buffer<float>::Ptr _posAttrBuf;
    us::Buffer<float>::Ptr _colorAttrBuf;

    // Attributes
    us::Attribute::Ptr _posAttr;
    us::Attribute::Ptr _colorAttr;

    // Uniforms
    us::Uniform::Ptr _mvpMatrixUnif;

    us::UniShader* _renderEngine;
};

#endif
