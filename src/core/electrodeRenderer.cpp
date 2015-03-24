#include "electrodeRenderer.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

ElectrodeRenderer::ElectrodeRenderer(ElectrodeMap *electrodeMap) :
    _electrodeMap(electrodeMap),
    _electrodeCount(0)
{
}

ElectrodeRenderer::~ElectrodeRenderer()
{
    _renderEngine->disconnectProgram();
    delete _renderEngine;
    _renderEngine = nullptr;
}

void ElectrodeRenderer::init()
{
    _renderEngine = new us::UniShader();
    initializeShaders();
}

void ElectrodeRenderer::render()
{
    _renderEngine->render(us::PrimitiveType::POINTS, _electrodeCount);
}

void ElectrodeRenderer::reloadShaders()
{
    if (_renderEngine != nullptr)
    {
        _renderEngine->disconnectProgram();
        delete _renderEngine;
        _renderEngine = new us::UniShader();
    }
    initializeShaders();
}
