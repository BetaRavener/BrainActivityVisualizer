// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include <GL/glew.h>

#include "openglwidget.h"

#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <GL/glew.h>

#include <stdexcept>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      _initialized(false)
{
}

void OpenGLWidget::render()
{

}

void OpenGLWidget::paintGL()
{
    if (!_initialized)
        throw std::runtime_error("Uninitialized");

    activateGlewContext();
    render();
    deactivateGlewContext();
}

void OpenGLWidget::initialize()
{
}

void OpenGLWidget::initializeGL()
{
    initGlewContext();
    activateGlewContext();
    initialize();
    deactivateGlewContext();
    _initialized = true;
}

void OpenGLWidget::activateGL()
{
    makeCurrent();
    activateGlewContext();
}

void OpenGLWidget::deactivateGL()
{
    deactivateGlewContext();
    doneCurrent();
}
