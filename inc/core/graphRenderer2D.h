// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef GRAPH_RENDERER_2D_H
#define GRAPH_RENDERER_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>

#include "graphItem2D.h"

/**
 * @brief The GraphRenderer2D class renders a chart view composed of multiple charts.
 */
class GraphRenderer2D
{
public:
    GraphRenderer2D();
    ~GraphRenderer2D();

    /**
     * @brief Initializes the class before usage.
     */
    void init();

    /**
     * @brief Updates the rendering configuration.
     * @param mvpMatrix ModelViewProjection matrix.
     */
    void update(glm::mat4 mvpMatrix);

    /**
     * @brief Renders a single chart item.
     * @param item The chart item.
     * @param zoom Vector specifying horizontal and vertical zoom for the item.
     * @param position Vector specifying the position of the item in graph.
     * @param size Vector specifying the size of the item.
     */
    void renderItem(const GraphItem2D& item, glm::vec2 zoom, glm::vec2 position, glm::vec2 size);

    /**
     * @brief Reloads and reinitializes the shader program.
     */
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
