// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "electrodeRenderer.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include "glmHelpers.h"

#include "GL/glew.h"

#include <QImage>
#include <QPainter>
#include <QString>

ElectrodeRenderer::ElectrodeRenderer() :
    _electrodeCount(0),
    _electrodesChanged(false)
{
}

ElectrodeRenderer::~ElectrodeRenderer()
{
}

void ElectrodeRenderer::init()
{
    _renderEngine = new us::UniShader();
    _namesEngine = new us::UniShader();
    _electrodePosAttrBuf = us::Buffer<float>::create();
    _electrodeColorAttrBuf = us::Buffer<float>::create();
    _namesBottomLeftUVAttrBuf = us::Buffer<float>::create();
    _namesTopRightUVAttrBuf = us::Buffer<float>::create();
    initializeShaders();
}

void ElectrodeRenderer::render()
{
    if (_electrodesChanged)
    {
        updateElectrodes();
        prepareNamesTexture();
        _electrodesChanged = false;
    }

    if (_electrodeCount > 0)
    {
        prepareColorBuffer();

        _renderEngine->render(us::PrimitiveType::POINTS, _electrodeCount);

        if (_showNames)
        {
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            _namesEngine->render(us::PrimitiveType::POINTS, _electrodeCount);
            glDisable(GL_BLEND);
        }
    }
}

void ElectrodeRenderer::update(glm::vec3 eyePos, glm::vec3 upDir, glm::vec3 rightDir, glm::mat4 mvpMatrix)
{
    _namesEyePosUnif->setSource(glm::value_ptr(eyePos), 3);
    _namesUpDirUnif->setSource(glm::value_ptr(upDir), 3);
    _namesRightDirUnif->setSource(glm::value_ptr(rightDir), 3);
    _namesMvpMatrixUnif->setSource(glm::value_ptr(mvpMatrix), 16);
}

void ElectrodeRenderer::electrodes(std::vector<Electrode::WeakPtr> electrodes)
{
    _electrodes = std::vector<Electrode::WeakPtr>();
    for (auto electrode : electrodes)
    {
        if (electrodePresent(electrode))
            _electrodes.push_back(electrode);
    }
    _electrodesChanged = true;
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

void ElectrodeRenderer::showNames(bool show)
{
    _showNames = show;
}

void ElectrodeRenderer::initializeShaders()
{
    auto vertexShader = us::ShaderObject::create();
    vertexShader->loadFile("shaders/electrodeNames.vert");

    auto geometryShader = us::ShaderObject::create();
    geometryShader->loadFile("shaders/electrodeNames.geom");

    auto fragmentShader = us::ShaderObject::create();
    fragmentShader->loadFile("shaders/electrodeNames.frag");

    auto program = us::ShaderProgram::create();
    program->addShaderObject(vertexShader);
    program->addShaderObject(geometryShader);
    program->addShaderObject(fragmentShader);
    program->ensureLink();

    auto input = program->getInput();
    _namesPosAttr = input->addAttribute("position");
    _namesBottomLeftUVAttr = input->addAttribute("bottomLeftUV");
    _namesTopRightUVAttr = input->addAttribute("topRightUV");
    _namesEyePosUnif = input->addUniform("eyePos");
    _namesUpDirUnif = input->addUniform("upDir");
    _namesRightDirUnif = input->addUniform("rightDir");
    _namesTextureUnif = input->addUniform("namesTextureSampler");
    _namesMvpMatrixUnif = input->addUniform("mvpMatrix");
    _namesTextureAspectUnif = input->addUniform("textureAspect");

    _namesPosAttr->connectBuffer(_electrodePosAttrBuf);
    _namesPosAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _namesBottomLeftUVAttr->connectBuffer(_namesBottomLeftUVAttrBuf);
    _namesBottomLeftUVAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _namesTopRightUVAttr->connectBuffer(_namesTopRightUVAttrBuf);
    _namesTopRightUVAttr->setReadingMode(us::Attribute::ReadingMode::FLOAT);

    _namesEngine->connectProgram(program);
}

void ElectrodeRenderer::prepareNamesTexture()
{
    if (_electrodes.size() == 0)
        return;

    int maxHorizontal = 2048;
    QSize imageSize(2048,0);
    QPoint currentPos(0,0);
    int currentLineHeight = 0;

    QFont font("Times", 50, QFont::Bold);
    QFontMetrics metrics(font);

    std::vector<QRect> electrodeNameRects;

    for (unsigned int i = 0; i < _electrodes.size(); i++)
    {
        QString str = QString::fromStdString(_electrodes[i]->name());
        QRect rect = metrics.boundingRect(str);

        if (currentPos.x() + rect.width() + 1 > maxHorizontal)
        {
            imageSize.setHeight(imageSize.height() + currentLineHeight);
            currentPos.setX(0);
            currentPos.setY(currentPos.y() + currentLineHeight);
            currentLineHeight = 0;
        }

        rect.moveTopLeft(currentPos);
        electrodeNameRects.push_back(rect);
        currentPos = rect.topRight();
        currentPos.setX(currentPos.x() + 1);
        if (rect.height() > currentLineHeight)
            currentLineHeight = rect.height();
    }
    imageSize.setHeight(imageSize.height() + currentLineHeight);
    imageSize.setHeight(glm::Helpers::geqPow2(imageSize.height()));

    QImage img(imageSize, QImage::Format_RGBA8888);
    QPainter painter(&img);
    painter.setPen(Qt::white);
    painter.setFont(font);

    std::vector<float> bottomLeftVec;
    std::vector<float> topRightVec;
    for (unsigned int i = 0; i < electrodeNameRects.size(); i++)
    {
        QString str = QString::fromStdString(_electrodes[i]->name());
        painter.drawText(electrodeNameRects[i], str);

        QRect& rect = electrodeNameRects[i];
        glm::Helpers::pushBack(bottomLeftVec,
                               glm::vec2((float)rect.left() / imageSize.width(),
                                         (float)rect.bottom() / imageSize.height()));
        glm::Helpers::pushBack(topRightVec,
                               glm::vec2((float)rect.right() / imageSize.width(),
                                         (float)rect.top() / imageSize.height()));
    }
    painter.end();

    _namesBottomLeftUVAttrBuf->setData(bottomLeftVec);
    _namesTopRightUVAttrBuf->setData(topRightVec);

    us::Texture::Ptr texture = us::Texture::create(us::Texture::TextureType::TWO_DIM);
    texture->setData(img.constBits(), imageSize.width(), imageSize.height());
    texture->setMipmaping(true);
    _namesTextureUnif->setSource(texture);
    _namesTextureAspectUnif->setSource((float)imageSize.width() / imageSize.height());
}
