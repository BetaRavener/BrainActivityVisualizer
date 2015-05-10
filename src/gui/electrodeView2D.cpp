#include "electrodeView2D.h"

#include <QMouseEvent>
#include <QWheelEvent>

#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

ElectrodeView2D::ElectrodeView2D(QWidget *parrent) :
    OpenGLWidget(parrent),
    _electrodeRenderer(new ElectrodeRenderer2D()),
    _electrodeAreaSize(100),
    m_frame(0),
    _showFps(false)
{
}

ElectrodeView2D::~ElectrodeView2D()
{
    activateGL();

    delete _electrodeRenderer;
    _electrodeRenderer = nullptr;

    deactivateGL();
}

void ElectrodeView2D::initialize()
{
    installEventFilter(this);

    _electrodeRenderer->init();

    _cam.Reset(true);
    _cam.InvertY();
    _cam.ZoomR(-100);

    _moveSensitivity = 1.0f;
    _scrollSensitivity = 5.0f;
}

void ElectrodeView2D::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projMatrix = glm::perspective(45.0f, (float)width() / (float)height(), 0.1f, 1000.0f);
    glm::mat4 viewMatrix = glm::lookAt(_cam.GetEye(), _cam.GetLookAt(), _cam.GetUp());
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 matrix = projMatrix * modelViewMatrix;

    _electrodeRenderer->update(_cam.GetEye(), _cam.GetUp(), _cam.GetRight(), matrix);
    _electrodeRenderer->render();

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

bool ElectrodeView2D::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    bool needsRepaint = false;

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_R)
        {
            _cam.Reset(true);
            _cam.InvertY();
            _cam.ZoomR(-200);
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
        else if (keyEvent->key() == Qt::Key_L)
        {
            activateGL();
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

        if (mouseEvent->buttons().testFlag(Qt::RightButton))
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

void ElectrodeView2D::electrodes(std::vector<Electrode::WeakPtr> electrodes)
{
    _electrodeRenderer->electrodes(electrodes);
}
