#include "electrodeView3D.h"

#include <QMouseEvent>
#include <QWheelEvent>

#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

ElectrodeView3D::ElectrodeView3D(QWidget *parrent) :
    OpenGLWidget(parrent),
    _electrodeMap(nullptr),
    m_frame(0),
    _showFps(false),
    _showCrosshair(false)
{
}

ElectrodeView3D::~ElectrodeView3D()
{
}

void ElectrodeView3D::initialize()
{
    installEventFilter(this);

    _brainRenderer = new BrainRenderer();

    _electrodeRenderer = new ElectrodeRenderer3D(_electrodeMap);
    _electrodeRenderer->init();

    _cam.Reset(true);
    _cam.InvertY();
    _cam.ZoomR(-200);

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

    _electrodeRenderer->update(_cam.GetEye(), matrix);
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

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_R)
        {
            _cam.Reset(true);
            _cam.InvertY();
            _cam.ZoomR(-200);
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
        }

        else if (mouseEvent->buttons().testFlag(Qt::MiddleButton))
        {
            movVector *= _moveSensitivity;
            _cam.MoveR(glm::vec3(.0, .0, -movVector.y));
        }

        else if (mouseEvent->buttons().testFlag(Qt::RightButton))
        {
            movVector *= _moveSensitivity;
            _cam.MoveR(movVector);
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
        }
    }
    return false;
}

void ElectrodeView3D::electrodeMap(ElectrodeMap *electrodeMap)
{
    _electrodeMap = electrodeMap;
}
