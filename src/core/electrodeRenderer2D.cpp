// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "electrodeRenderer2D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include "glmHelpers.h"

ElectrodeRenderer2D::ElectrodeRenderer2D() :
    _spacingRadius(1)
{
}

void ElectrodeRenderer2D::update(glm::vec3 eyePos, glm::vec3 upDir, glm::vec3 rightDir, glm::mat4 mvpMatrix)
{
    ElectrodeRenderer::update(eyePos, upDir, rightDir, mvpMatrix);
    _radiusUnif->setSource(2.5f);
    _mvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void ElectrodeRenderer2D::setSpacingRadius(float radius)
{
    _spacingRadius = radius;
    _electrodesChanged = true;
}

void ElectrodeRenderer2D::initializeShaders()
{
    ElectrodeRenderer::initializeShaders();

    auto vertexShader = us::ShaderObject::create();
    vertexShader->loadFile("shaders/electrodesOrtho.vert");

    auto geometryShader = us::ShaderObject::create();
    geometryShader->loadFile("shaders/electrodesOrtho.geom");

    auto fragmentShader = us::ShaderObject::create();
    fragmentShader->loadFile("shaders/electrodesOrtho.frag");

    auto program = us::ShaderProgram::create();
    program->addShaderObject(vertexShader);
    program->addShaderObject(geometryShader);
    program->addShaderObject(fragmentShader);
    program->ensureLink();

    auto input = program->getInput();
    _electrodePosAttr = input->addAttribute("position");
    _electrodeColorAttr = input->addAttribute("vColor");
    _radiusUnif = input->addUniform("radius");
    _mvpMatrixUnif = input->addUniform("mvpMatrix");

    _electrodePosAttr->connectBuffer(_electrodePosAttrBuf);
    _electrodePosAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _electrodeColorAttr->connectBuffer(_electrodeColorAttrBuf);
    _electrodeColorAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _renderEngine->connectProgram(program);
}

void ElectrodeRenderer2D::prepareColorBuffer()
{
    std::vector<float> colors;
    colors.reserve(_electrodeCount * 3);

    for (auto electrode : _electrodes)
    {
        if (electrode->has2D())
        {
            glm::vec3 color = electrode->color();
            glm::Helpers::pushBack(colors, color);
        }
    }

    _electrodeColorAttrBuf->setData(colors);
}

void ElectrodeRenderer2D::updateElectrodes()
{
    // Prepare positions for buffer
    std::vector<float> electrodePos;
    _electrodeCount = 0;
    for (auto electrode : _electrodes)
    {
        if (electrode->has2D())
        {
            glm::vec3 pos = glm::vec3(electrode->position2D(), 0) * _spacingRadius;
            glm::Helpers::pushBack(electrodePos, pos);
            _electrodeCount++;
        }
    }

    _electrodePosAttrBuf->setData(electrodePos);
}

bool ElectrodeRenderer2D::electrodePresent(Electrode::WeakPtr electrode)
{
    return electrode->has2D();
}
