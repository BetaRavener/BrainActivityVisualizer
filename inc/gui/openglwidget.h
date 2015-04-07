#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "glewContextSupport.h"
#include <QOpenGLWidget>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class OpenGLWidget : public QOpenGLWidget, private GlewContextSupport
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);

    virtual void render();
    virtual void paintGL();

    virtual void initialize();
    virtual void initializeGL();

public slots:
    void updateElectrodes();

protected:

    void activateGL();
    void deactivateGL();
};

#endif
