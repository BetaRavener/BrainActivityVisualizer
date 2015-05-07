#ifndef ELECTRODE_VIEW_2D
#define ELECTRODE_VIEW_2D

#include "openglwidget.h"

#include <QPoint>
#include <QElapsedTimer>

#include "electrodeRenderer2D.h"
#include "hybridCam.h"

class ElectrodeView2D : public OpenGLWidget
{
public:
    ElectrodeView2D(QWidget *parrent = 0);
    ~ElectrodeView2D();

    virtual void initialize();
    virtual void render();
    bool eventFilter(QObject *obj, QEvent *event);

    void electrodes(std::vector<Electrode::WeakPtr> electrodes);

private:
    ElectrodeRenderer2D* _electrodeRenderer;

    HybridCam _cam;

    // Input variables
    QPoint _prevMousePos;
    float _moveSensitivity;
    float _scrollSensitivity;

    int m_frame;

    bool _showFps;
    QElapsedTimer _fpsTimer;
    int _lastFpsFrame;
};

#endif
