#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

signals:

public slots:

protected:
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);
};

#endif // GLWIDGET_H
