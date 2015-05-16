// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "electrodeView3D.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QMessageBox>

#include <iostream>
#include <string>
#include <stdexcept>

#include <glm/gtc/matrix_transform.hpp>

ElectrodeView3D::ElectrodeView3D(QWidget *parrent) :
    OpenGLWidget(parrent),
    _brainRenderer(new BrainRenderer()),
    _electrodeRenderer(new ElectrodeRenderer3D()),
    m_frame(0),
    _showFps(false),
    _showCrosshair(false)
{
}

ElectrodeView3D::~ElectrodeView3D()
{
    activateGL();

    delete _brainRenderer;
    _brainRenderer = nullptr;

    delete _electrodeRenderer;
    _electrodeRenderer = nullptr;

    deactivateGL();
}

void ElectrodeView3D::initialize()
{
    installEventFilter(this);

    _brainRenderer->init();
    _electrodeRenderer->init();

    resetView();

    _rotateSensitivity = .01f;
    _moveSensitivity = 1.0f;
    _scrollSensitivity = 5.0f;
}

void ElectrodeView3D::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glDepthMask(GL_TRUE);

    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projMatrix = glm::perspective(45.0f, (float)width() / (float)height(), 0.1f, 1000.0f);
    glm::mat4 viewMatrix = glm::lookAt(_cam.GetEye(), _cam.GetLookAt(), _cam.GetUp());
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 matrix = projMatrix * modelViewMatrix;

    _brainRenderer->update(_cam.GetEye(), matrix, modelMatrix);
    _brainRenderer->render();

    _electrodeRenderer->update(_cam.GetEye(), _cam.GetUp(), _cam.GetRight(), matrix);
    _electrodeRenderer->render();


    if (_showCrosshair)
    {
        //TODO: use shader
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_MULTISAMPLE);

    ++m_frame;

    if (_showFps)
    {
        qint64 elapsed = _fpsTimer.elapsed();
        if (elapsed > 1000)
        {
            double fps = (double)(m_frame - _lastFpsFrame) / elapsed * 1000.0;
            std::cout << fps << std::endl;
            _lastFpsFrame = m_frame;
            _fpsTimer.restart();
        }
    }
}

bool ElectrodeView3D::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    bool needsRepaint = false;

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_R)
        {
            resetView();
            needsRepaint = true;
        }
        else if (keyEvent->key() == Qt::Key_F)
        {
            _showFps = !_showFps;
            if (_showFps)
            {
                _lastFpsFrame = m_frame;
                _fpsTimer.start();
            }
            else
            {
                _fpsTimer.invalidate();
            }
        }
        else if (keyEvent->key() == Qt::Key_C)
        {
            _showCrosshair = !_showCrosshair;
        }
        else if (keyEvent->key() == Qt::Key_L)
        {
            activateGL();
            _brainRenderer->reloadShaders();
            _electrodeRenderer->reloadShaders();
            deactivateGL();
            needsRepaint = true;
        }
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        _prevMousePos = mouseEvent->pos();
    }
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        QPoint curMousePos = mouseEvent->pos();
        glm::vec3 movVector(curMousePos.x() - _prevMousePos.x(),
                            curMousePos.y() - _prevMousePos.y(),
                            .0);

        if (mouseEvent->buttons().testFlag(Qt::LeftButton))
        {
            movVector *= _rotateSensitivity;
            _cam.RotateR(glm::vec3(movVector.y, movVector.x, .0));
            needsRepaint = true;
        }

        else if (mouseEvent->buttons().testFlag(Qt::MiddleButton))
        {
            movVector *= _moveSensitivity;
            _cam.MoveR(glm::vec3(.0, .0, -movVector.y));
            needsRepaint = true;
        }

        else if (mouseEvent->buttons().testFlag(Qt::RightButton))
        {
            movVector *= _moveSensitivity;
            _cam.MoveR(movVector);
            needsRepaint = true;
        }

        _prevMousePos = curMousePos;
    }
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        if(!wheelEvent->angleDelta().isNull())
        {
            QPoint numDegrees = wheelEvent->angleDelta() / 8;
            QPoint numSteps = numDegrees / 15;

            _cam.ZoomR(numSteps.y() * _scrollSensitivity);
            needsRepaint = true;
        }
    }

    if (needsRepaint)
        repaint();

    return false;
}

void ElectrodeView3D::electrodes(std::vector<Electrode::WeakPtr> electrodes)
{
    _electrodeRenderer->electrodes(electrodes);
}

void ElectrodeView3D::resetView(bool repaintView)
{
    _cam.Reset(true);
    _cam.InvertY();
    _cam.ZoomR(-200);
    if (repaintView)
        repaint();
}

void ElectrodeView3D::showElectrodeNames(bool show)
{
    _electrodeRenderer->showNames(show);
    repaint();
}
