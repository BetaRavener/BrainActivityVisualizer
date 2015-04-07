#ifndef GRAPH_RENDERER_2D_H
#define GRAPH_RENDERER_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>

#include "graphItem2D.h"

class GraphRenderer2D
{
public:
    GraphRenderer2D();
    ~GraphRenderer2D();

    void init();

    void update(glm::mat4 mvpMatrix);

    void renderItem(const GraphItem2D& item, glm::vec2 zoom, glm::vec2 position, glm::vec2 size);

    void reloadShaders();

private:
    void initializeShaders();

    unsigned int _valueCount;

    // Buffers
    us::Buffer<float>::Ptr _posAttrBuf;
    us::Buffer<unsigned int>::Ptr _indicesBuf;

    // Attributes
    us::Attribute::Ptr _posAttr;

    // Uniforms
    us::Uniform::Ptr _zoomUnif;
    us::Uniform::Ptr _sampleSpacingUnif;
    us::Uniform::Ptr _horizontalShiftUnif;
    us::Uniform::Ptr _widthUnif;
    us::Uniform::Ptr _lineColorUnif;
    us::Uniform::Ptr _mvpMatrixUnif;
    us::Uniform::Ptr _bottomLeftUnif;
    us::Uniform::Ptr _sizeUnif;

    us::UniShader* _renderEngine;
};

#endif
