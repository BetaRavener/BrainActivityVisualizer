#include "electrodeRenderer3D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

ElectrodeRenderer3D::ElectrodeRenderer3D(ElectrodeMap *electrodeMap) :
    ElectrodeRenderer(electrodeMap)
{
}

void ElectrodeRenderer3D::update(glm::vec3 eyePos, glm::mat4 mvpMatrix)
{
    _radiusUnif->setSource(3.0f);
    _eyePosUnif->setSource(glm::value_ptr(eyePos), 3);
    _mvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void ElectrodeRenderer3D::initializeShaders()
{
    // Prepare positions for buffer
    std::vector<float> electrodePos;
    _electrodeCount = 0;
    for (auto electrodePair : _electrodeMap->allElectrodes())
    {
        Electrode& electrode = electrodePair.second;

        if (electrode.has3D())
        {
            glm::vec3 pos = electrode.position3D();
            electrodePos.push_back(pos.x);
            electrodePos.push_back(pos.y);
            electrodePos.push_back(pos.z);
            _electrodeCount++;
        }
    }

    _electrodePosAttrBuf = us::Buffer<float>::create();
    _electrodePosAttrBuf->setData(electrodePos);

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
    _radiusUnif = input->addUniform("radius");
    _eyePosUnif = input->addUniform("eyePos");
    _mvpMatrixUnif = input->addUniform("mvpMatrix");

    _electrodePosAttr->connectBuffer(_electrodePosAttrBuf);
    _electrodePosAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _renderEngine->connectProgram(program);
}
