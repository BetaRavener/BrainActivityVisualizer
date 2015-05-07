#include "electrodeRenderer3D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include "glmHelpers.h"

ElectrodeRenderer3D::ElectrodeRenderer3D()
{
}

void ElectrodeRenderer3D::update(glm::vec3 eyePos, glm::vec3 upDir, glm::vec3 rightDir, glm::mat4 mvpMatrix)
{
    ElectrodeRenderer::update(eyePos, upDir, rightDir, mvpMatrix);
    _radiusUnif->setSource(3.0f);
    _eyePosUnif->setSource(glm::value_ptr(eyePos), 3);
    _mvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void ElectrodeRenderer3D::initializeShaders()
{
    ElectrodeRenderer::initializeShaders();

    auto vertexShader = us::ShaderObject::create();
    vertexShader->loadFile("shaders/electrodes.vert");

    auto geometryShader = us::ShaderObject::create();
    geometryShader->loadFile("shaders/electrodes.geom");

    auto fragmentShader = us::ShaderObject::create();
    fragmentShader->loadFile("shaders/electrodes.frag");

    auto program = us::ShaderProgram::create();
    program->addShaderObject(vertexShader);
    program->addShaderObject(geometryShader);
    program->addShaderObject(fragmentShader);
    program->ensureLink();

    auto input = program->getInput();
    _electrodePosAttr = input->addAttribute("position");
    _electrodeColorAttr = input->addAttribute("vColor");
    _radiusUnif = input->addUniform("radius");
    _eyePosUnif = input->addUniform("eyePos");
    _mvpMatrixUnif = input->addUniform("mvpMatrix");

    _electrodePosAttr->connectBuffer(_electrodePosAttrBuf);
    _electrodePosAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _electrodeColorAttr->connectBuffer(_electrodeColorAttrBuf);
    _electrodeColorAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _renderEngine->connectProgram(program);
}

void ElectrodeRenderer3D::prepareColorBuffer()
{
    std::vector<float> colors;
    colors.reserve(_electrodeCount * 3);

    for (auto electrode : _electrodes)
    {
        if (electrode->has3D())
        {
            glm::vec3 color = electrode->color();
            glm::Helpers::pushBack(colors, color);
        }
    }

    _electrodeColorAttrBuf->setData(colors);
}

void ElectrodeRenderer3D::updateElectrodes()
{
    // Prepare positions for buffer
    std::vector<float> electrodePos;
    _electrodeCount = 0;
    for (auto electrode : _electrodes)
    {
        if (electrode->has3D())
        {
            glm::vec3 pos = electrode->position3D();
            glm::Helpers::pushBack(electrodePos, pos);
            _electrodeCount++;
        }
    }

    _electrodePosAttrBuf->setData(electrodePos);
}

bool ElectrodeRenderer3D::electrodePresent(Electrode::WeakPtr electrode)
{
    return electrode->has3D();
}
