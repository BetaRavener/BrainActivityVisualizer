// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef GRAPH_GRID_2D_H
#define GRAPH_GRID_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>

/**
 * @brief The ShapeRenderer2D class represents a general renderer which can be used to draw
 * 2D geometry.
 */
class ShapeRenderer2D
{
public:
    ShapeRenderer2D();
    ~ShapeRenderer2D();

    /**
     * @brief Initializes the renderer.
     */
    void init();

    /**
     * @brief Updates the brain renderer configuration.
     * @param mvpMatrix ModelViewProjection matrix that manipualtes 3D space.
     */
    void update(glm::mat4 mvpMatrix);

    /**
     * @brief Renders the stored data as 2D geometry.
     * @param type Specifies how the data will be represented.
     * @param count The number of items.
     */
    void render(us::PrimitiveType type, unsigned int count);

    /**
     * @brief Setter.
     * @param positions The position data for geometry.
     */
    void setPositions(const std::vector<float>& positions);

    /**
     * @brief Setter.
     * @param colors The color data for geometry.
     */
    void setColors(const std::vector<float>& colors);

    /**
     * @brief Reloads and reinitializes the shader program.
     */
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
