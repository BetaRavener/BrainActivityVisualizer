#include "brainRenderer.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

BrainRenderer::BrainRenderer()
{
    // Load the 3d model from the file
    std::string err = tinyobj::LoadObj(_shapes, _materials, "models/brain-hi-res.obj");

    if (!err.empty()) {
      std::cerr << err << std::endl;
      exit(1);
    }

    initializeShaders();
}

void BrainRenderer::update(glm::vec3 eyePos, glm::mat4 mvpMatrix, glm::mat4 modelMatrix)
{
    float brainColor[3] = {1, 1, 1};
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

    _eyePosUnif->setSource(glm::value_ptr(eyePos), 3);
    _matrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
    _modelViewMatrixUnif->setSource(glm::value_ptr(modelMatrix), 16);
    _normalMatrixUnif->setSource(glm::value_ptr(normalMatrix), 16);
    _brainColorUnif->setSource(brainColor, 3);
}

void BrainRenderer::render()
{
    for (unsigned int i = 0; i < _posAttrBufs.size(); i++)
    {
        _posAttr->connectBuffer(_posAttrBufs[i]);
        _colAttr->connectBuffer(_colAttrBufs[i]);
        _renderEngine->renderElements(_indicesBufs[i], us::PrimitiveType::TRIANGLES, _indicesCounts[i]);
    }
}

void BrainRenderer::reloadShaders()
{
    if (_renderEngine != nullptr)
    {
        delete _renderEngine;
        _renderEngine = new us::UniShader();

        _posAttrBufs.clear();
        _colAttrBufs.clear();
        _indicesBufs.clear();
        _indicesCounts.clear();

        initializeShaders();
    }
}

void BrainRenderer::initializeShaders()
{
    auto vertexShader = us::ShaderObject::create();
    vertexShader->loadFile("shaders/brain.vert");

    auto fragmentShader = us::ShaderObject::create();
    fragmentShader->loadFile("shaders/brain.frag");

    auto program = us::ShaderProgram::create();
    program->addShaderObject(vertexShader);
    program->addShaderObject(fragmentShader);
    program->ensureLink();

    auto input = program->getInput();
    _posAttr = input->addAttribute("posAttr");
    _colAttr = input->addAttribute("normalAttr");
    _eyePosUnif = input->addUniform("eyePos");
    //_lookAtUnif = input->addUniform("lookAt");
    _matrixUnif = input->addUniform("matrix");
    _modelViewMatrixUnif = input->addUniform("modelViewMatrix");
    _normalMatrixUnif = input->addUniform("normalMatrix");
    _brainColorUnif = input->addUniform("brainColor");

    _posAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);
    _colAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _renderEngine = new us::UniShader();
    _renderEngine->connectProgram(program);

    for (unsigned int i = 0; i < _shapes.size(); i++)
    {
        us::Buffer<float>::Ptr posAttrBuf = us::Buffer<float>::create();
        auto colAttrBuf = us::Buffer<float>::create();
        auto indicesBuf = us::Buffer<unsigned int>::create();

        posAttrBuf->setData(_shapes[i].mesh.positions);
        colAttrBuf->setData(_shapes[i].mesh.normals);
        indicesBuf->setData(_shapes[i].mesh.indices);
        _posAttrBufs.push_back(posAttrBuf);
        _colAttrBufs.push_back(colAttrBuf);
        _indicesBufs.push_back(indicesBuf);
        _indicesCounts.push_back(_shapes[i].mesh.indices.size());
    }
}
