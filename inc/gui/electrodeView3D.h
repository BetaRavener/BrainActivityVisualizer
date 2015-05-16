// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODE_VIEW_3D
#define ELECTRODE_VIEW_3D

#include "openglwidget.h"

#include <QPoint>
#include <QElapsedTimer>

#include "brainRenderer.h"
#include "electrodeRenderer3D.h"
#include "hybridCam.h"

/**
 * @brief The ElectrodeView3D class represents a 3D electrode view.
 */
class ElectrodeView3D : public OpenGLWidget
{
    Q_OBJECT

public:
    ElectrodeView3D(QWidget *parrent = 0);
    ~ElectrodeView3D();

    /**
     * @brief Initializes view before usage.
     */
    virtual void initialize();

    /**
     * @brief Renders the whole view.
     */
    virtual void render();

    /**
     * @brief Processes the events for the view such as mouse panning, zooming, etc.
     * @param obj Object that received the event.
     * @param event Event that occured.
     * @return True if the event was processed.
     */
    bool eventFilter(QObject *obj, QEvent *event);

    /**
     * @brief Setter.
     * @param electrodes Electrodes that are rendered in the view.
     */
    void electrodes(std::vector<Electrode::WeakPtr> electrodes);

    /**
     * @brief Resets the view into default configuration.
     * @param repaintView If true, the repaint event will be issued.
     */
    void resetView(bool repaintView = false);

    /**
     * @brief Setter.
     * @param show If true, the electrode names will be rendered.
     */
    void showElectrodeNames(bool show);

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
