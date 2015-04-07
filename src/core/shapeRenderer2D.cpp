#include "shapeRenderer2D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

ShapeRenderer2D::ShapeRenderer2D() :
    _valueCount(0)
{
}

ShapeRenderer2D::~ShapeRenderer2D()
{
    _renderEngine->disconnectProgram();
    delete _renderEngine;
    _renderEngine = nullptr;
}

void ShapeRenderer2D::init()
{
    _renderEngine = new us::UniShader();
    initializeShaders();
}

void ShapeRenderer2D::reloadShaders()
{
    if (_renderEngine != nullptr)
    {
        _renderEngine->disconnectProgram();
        delete _renderEngine;
        _renderEngine = new us::UniShader();
    }
    initializeShaders();
}

void ShapeRenderer2D::update(glm::mat4 mvpMatrix)
{
    _mvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void ShapeRenderer2D::render(us::PrimitiveType type, unsigned int count)
{
    _renderEngine->render(type, count);
}

void ShapeRenderer2D::setPositions(const std::vector<float> &positions)
{
    _posAttrBuf->setData(positions);
}

void ShapeRenderer2D::setColors(const std::vector<float> &colors)
{
    _colorAttrBuf->setData(colors);
}

void ShapeRenderer2D::initializeShaders()
{
    auto vertexShader = us::ShaderObject::create();
    vertexShader->loadFile("shaders/shapes2D.vert");

    auto fragmentShader = us::ShaderObject::create();
    fragmentShader->loadFile("shaders/shapes2D.frag");

    auto program = us::ShaderProgram::create();
    program->addShaderObject(vertexShader);
    program->addShaderObject(fragmentShader);
    program->ensureLink();

    auto input = program->getInput();
    _posAttr = input->addAttribute("position");
    _colorAttr = input->addAttribute("vColor");
    _mvpMatrixUnif = input->addUniform("mvpMatrix");

    _posAttrBuf = us::Buffer<float>::create();
    _posAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);
    _posAttr->connectBuffer(_posAttrBuf);

    _colorAttrBuf = us::Buffer<float>::create();
    _colorAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);
    _colorAttr->connectBuffer(_colorAttrBuf);

    _renderEngine->connectProgram(program);
}
