#include "electrodeRenderer2D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

ElectrodeRenderer2D::ElectrodeRenderer2D(std::vector<Electrode::WeakPtr> electrodes) :
    ElectrodeRenderer(electrodes)
{
}

void ElectrodeRenderer2D::update(glm::mat4 mvpMatrix)
{
    _radiusUnif->setSource(2.5f);
    _mvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void ElectrodeRenderer2D::initializeShaders()
{
    // Prepare positions for buffer
    std::vector<float> electrodePos;
    _electrodeCount = 0;
    for (auto electrode : _electrodes)
    {
        if (electrode->has2D())
        {
            glm::vec2 pos = electrode->position2D();
            electrodePos.push_back(pos.x);
            electrodePos.push_back(pos.y);
            _electrodeCount++;
        }
    }

    _electrodePosAttrBuf->setData(electrodePos);

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
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
        }
    }

    _electrodeColorAttrBuf->setData(colors);
}
