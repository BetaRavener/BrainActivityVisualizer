#include "graphGrid2D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

GraphGrid2D::GraphGrid2D() :
    _valueCount(0)
{
}

GraphGrid2D::~GraphGrid2D()
{
    _renderEngine->disconnectProgram();
    delete _renderEngine;
    _renderEngine = nullptr;
}

void GraphGrid2D::init()
{
    _renderEngine = new us::UniShader();
    initializeShaders();
}

void GraphGrid2D::reloadShaders()
{
    if (_renderEngine != nullptr)
    {
        _renderEngine->disconnectProgram();
        delete _renderEngine;
        _renderEngine = new us::UniShader();
    }
    initializeShaders();
}

void GraphGrid2D::setGrid(std::vector<float> horizontal, std::vector<float> vertical, glm::vec2 winSize)
{
    std::vector<float> lines;
    _valueCount = 0;

    for (auto y : horizontal)
    {
        lines.push_back(0);
        lines.push_back(y);
        lines.push_back(winSize.x);
        lines.push_back(y);
        _valueCount += 4;
    }

    for (auto x : vertical)
    {
        lines.push_back(x);
        lines.push_back(0);
        lines.push_back(x);
        lines.push_back(winSize.y);
        _valueCount += 4;
    }

    _posAttrBuf->setData(lines);
}

void GraphGrid2D::update(glm::mat4 mvpMatrix)
{
    _shapeColorUnif->setSource(glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)), 3);
    _mvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void GraphGrid2D::render()
{
    _renderEngine->render(us::PrimitiveType::LINES, _valueCount);
}

void GraphGrid2D::initializeShaders()
{
    auto vertexShader = us::ShaderObject::create();
    vertexShader->loadFile("shaders/graphGrid2D.vert");

    auto fragmentShader = us::ShaderObject::create();
    fragmentShader->loadFile("shaders/graphGrid2D.frag");

    auto program = us::ShaderProgram::create();
    program->addShaderObject(vertexShader);
    program->addShaderObject(fragmentShader);
    program->ensureLink();

    auto input = program->getInput();
    _posAttr = input->addAttribute("position");
    _shapeColorUnif = input->addUniform("shapeColor");
    _mvpMatrixUnif = input->addUniform("mvpMatrix");

    _posAttrBuf = us::Buffer<float>::create();
    _posAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);
    _posAttr->connectBuffer(_posAttrBuf);

    _renderEngine->connectProgram(program);
}
