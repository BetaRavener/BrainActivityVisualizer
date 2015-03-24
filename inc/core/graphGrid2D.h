#ifndef GRAPH_GRID_2D_H
#define GRAPH_GRID_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>

class GraphGrid2D
{
public:
    GraphGrid2D();
    ~GraphGrid2D();

    void init();

    void update(glm::mat4 mvpMatrix);

    void render();

    void reloadShaders();

    void setGrid(std::vector<float> horizontal, std::vector<float> vertical, glm::vec2 winSize);

private:
    void initializeShaders();

    unsigned int _valueCount;

    // Buffers
    us::Buffer<float>::Ptr _posAttrBuf;

    // Attributes
    us::Attribute::Ptr _posAttr;

    // Uniforms
    us::Uniform::Ptr _shapeColorUnif;
    us::Uniform::Ptr _mvpMatrixUnif;

    us::UniShader* _renderEngine;
};

#endif
