#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void GLWidget::paintGL()
{
    glClearColor(0,0,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex3i(10, -5, -10);
    glVertex3i(0, 5, -10);
    glVertex3i(-10, -5, -10);
    glEnd();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
