// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "graphRenderer2D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

GraphRenderer2D::GraphRenderer2D() :
    _valueCount(0)
{
}

GraphRenderer2D::~GraphRenderer2D()
{
    _renderEngine->disconnectProgram();
    delete _renderEngine;
    _renderEngine = nullptr;
}

void GraphRenderer2D::init()
{
    _renderEngine = new us::UniShader();
    initializeShaders();
}

void GraphRenderer2D::reloadShaders()
{
    if (_renderEngine != nullptr)
    {
        _renderEngine->disconnectProgram();
        delete _renderEngine;
        _renderEngine = new us::UniShader();
    }
    initializeShaders();
}

void GraphRenderer2D::update(glm::mat4 mvpMatrix)
{
    _widthUnif->setSource(1.f);
    _lineColorUnif->setSource(glm::value_ptr(glm::vec3(1.f, 1.f, 1.f)), 3);
    _mvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void GraphRenderer2D::renderItem(const GraphItem2D& item, glm::vec2 zoom, glm::vec2 position, glm::vec2 size)
{
    _zoomUnif->setSource(glm::value_ptr(glm::vec2(zoom.x, zoom.y * item.verticalZoom())), 2);
    _sampleSpacingUnif->setSource(item.sampleSpacing());
    _bottomLeftUnif->setSource(glm::value_ptr(position), 2);
    _sizeUnif->setSource(glm::value_ptr(size), 2);
    _posAttr->connectBuffer(item.positions());
    _renderEngine->renderElements(item.indices(), us::PrimitiveType::LINE_STRIP_ADJACENCY, item.valueCount() + 2);
}

void GraphRenderer2D::initializeShaders()
{
    auto vertexShader = us::ShaderObject::create();
    vertexShader->loadFile("shaders/graph2D.vert");

    auto geometryShader = us::ShaderObject::create();
    geometryShader->loadFile("shaders/graph2D.geom");

    auto fragmentShader = us::ShaderObject::create();
    fragmentShader->loadFile("shaders/graph2D.frag");

    auto program = us::ShaderProgram::create();
    program->addShaderObject(vertexShader);
    program->addShaderObject(geometryShader);
    program->addShaderObject(fragmentShader);
    program->ensureLink();

    auto input = program->getInput();
    _posAttr = input->addAttribute("position");
    _zoomUnif = input->addUniform("zoom");
    _sampleSpacingUnif = input->addUniform("sampleSpacing");
    _widthUnif = input->addUniform("width");
    _lineColorUnif = input->addUniform("lineColor");
    _mvpMatrixUnif = input->addUniform("mvpMatrix");
    _bottomLeftUnif = input->addUniform("bottomLeft");
    _sizeUnif = input->addUniform("size");

    _posAttrBuf = us::Buffer<float>::create();
    _posAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _indicesBuf = us::Buffer<unsigned int>::create();

    _renderEngine->connectProgram(program);
}
