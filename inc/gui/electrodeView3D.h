#ifndef ELECTRODE_VIEW_3D
#define ELECTRODE_VIEW_3D

#include "openglwidget.h"

#include <QPoint>
#include <QElapsedTimer>

#include "brainRenderer.h"
#include "electrodeRenderer3D.h"
#include "hybridCam.h"

class ElectrodeView3D : public OpenGLWidget
{
public:
    ElectrodeView3D(QWidget *parrent = 0);
    ~ElectrodeView3D();

    virtual void initialize();
    virtual void render();
    bool eventFilter(QObject *obj, QEvent *event);

    void electrodes(std::vector<Electrode::WeakPtr> electrodes);

private:
    BrainRenderer* _brainRenderer;
    ElectrodeRenderer3D* _electrodeRenderer;

    HybridCam _cam;

    // Input variables
    QPoint _prevMousePos;
    float _rotateSensitivity;
    float _moveSensitivity;
    float _scrollSensitivity;

    int m_frame;

    bool _showFps;
    QElapsedTimer _fpsTimer;
    int _lastFpsFrame;

    bool _showCrosshair;
};

#endif
