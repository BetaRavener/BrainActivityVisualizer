// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "glewContextSupport.h"
#include <QOpenGLWidget>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

/**
 * @brief The OpenGLWidget class represents general widget capable of rendering with OpenGL.
 */
class OpenGLWidget : public QOpenGLWidget, private GlewContextSupport
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);

    /**
     * @brief Renders the geoemetry.
     */
    virtual void render() = 0;

    /**
     * @brief Sets the OpenGL and GLEW contexts associated with this widget as current and
     * renders the widget's geometry.
     */
    virtual void paintGL();


    /**
     * @brief Initializes widget before usage.
     */
    virtual void initialize() = 0;

    /**
     * @brief Initializes OpenGL context before usage.
     */
    virtual void initializeGL();

protected:

    /**
     * @brief Activates this widget by making its OpenGL context current.
     */
    void activateGL();

    /**
     * @brief Deactivates this widget by setting OpenGL context to default value.
     */
    void deactivateGL();

private:
    bool _initialized;
};

#endif
