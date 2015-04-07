#include "electrodeRenderer.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

ElectrodeRenderer::ElectrodeRenderer(std::vector<Electrode::WeakPtr> electrodes) :
    _electrodes(electrodes),
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
    _electrodePosAttrBuf = us::Buffer<float>::create();
    _electrodeColorAttrBuf = us::Buffer<float>::create();
    initializeShaders();
}

void ElectrodeRenderer::render()
{
    prepareColorBuffer();
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
