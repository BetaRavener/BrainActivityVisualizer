// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef GRAPH_VIEW_2D
#define GRAPH_VIEW_2D

#include "openglwidget.h"

#include <vector>

#include <QMenu>
#include <QPoint>
#include <QElapsedTimer>
#include <QScrollBar>
#include <QLayout>

#include "graphRenderer2D.h"
#include "hybridCam.h"
#include "opensignalfiledialog.h"
#include "electrodeMap.h"
#include "graphItem2D.h"
#include "shapeRenderer2D.h"
#include "signalBatch.h"

/**
 * @brief The GraphView2D class represents a multichart view.
 */
class GraphView2D : public OpenGLWidget
{
    Q_OBJECT

signals:
    /**
     * @brief Fires when the user requested new animation time via this view.
     * @param time Requested animation time.
     */
    void requestTime(double time);

public:
    GraphView2D(QWidget *parrent = 0);
    ~GraphView2D();

    /**
     * @brief Initializes view before usage.
     */
    void initialize() Q_DECL_OVERRIDE;

    /**
     * @brief Renders the whole view.
     */
    void render() Q_DECL_OVERRIDE;

    /**
     * @brief Processes the events for the view such as mouse panning, zooming, etc.
     * @param obj Object that received the event.
     * @param event Event that occured.
     * @return True if the event was processed.
     */
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    /**
     * @brief Setter.
     * @param electrodeMap Electrode map that will be associated with the view.
     */
    void electrodeMap(ElectrodeMap* electrodeMap);

    /**
     * @brief Adds scroll bars which will be linked to this view. Moving the scrollbar will
     * affect the view and manipulation of view will update the scrollbars.
     * @param horizontal Horizontal scrollbar.
     * @param vertical Vertical scrollbar.
     */
    void addScrollBars(QScrollBar* horizontal, QScrollBar* vertical);

    /**
     * @brief Adds area designated for chart labels.
     * @param horizontal Horizontal label area.
     * @param vertical Vertical label area.
     */
    void addLabels(QLayout* horizontal, QLayout* vertical);

    /**
     * @brief Setter.
     * @param signalBatch Signal batch that will be associated with the view.
     */
    void signalBatch(SignalBatch::WeakPtr signalBatch);

public slots:
    /**
     * @brief Slot for updating the view after time has changed.
     * @param time New time.
     */
    void timeChanged(double time);

    /**
     * @brief Slot for updating the view after data changed.
     */
    void dataChanged();

    /**
     * @brief Slot for toggling the playback tracking.
     * @param track If true, the playback will be always in focus (i.e. tracked).
     */
    void trackPlayback(bool track);

private slots:
    void horizontallyScrolled(int value);
    void verticallyScrolled(int value);

private:
    void updateData(bool clearCache = false);
    void updateScrollBars();
    void updateLabels();
    void checkZoom();
    void checkView();
    int maxVericallScroll();
    void focusOnTime(double time);

    std::vector<float> horizontalSeparators();
    void prepareBackground(glm::vec3 firstColor = glm::vec3(0.f, 0.f, 0.f),
                           glm::vec3 secondColor = glm::vec3(0.25f, 0.25f, 0.25f));
    void prepareGrid(glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f),
                     glm::vec3 timeColor = glm::vec3(1.f, 1.f, 0.f));
    glm::vec2 itemSize();

    SignalBatch::WeakPtr _signalBatch;
    std::vector<GraphItem2D> _items;
    double _horizontalScrollMultiplier;

    QMenu _menu;

    // Data for shape renderer for drawing grid and background
    std::vector<float> _graphGrid;
    std::vector<float> _graphGridColor;
    unsigned int _graphGridCount;
    std::vector<float> _graphBackground;
    std::vector<float> _graphBackgroundColor;
    unsigned int _graphBackgroundCount;

    ShapeRenderer2D* _shapeRenderer;
    GraphRenderer2D* _graphRenderer;

    QScrollBar* _horizontalScrollBar;
    QScrollBar* _verticalScrollBar;
    QLayout* _horizontalLabels;
    QLayout* _verticalLabels;

    glm::vec2 _minZoom;
    glm::vec2 _maxZoom;
    glm::vec2 _zoom;

    int _middleSample;
    int _verticalScroll;
    bool _updatingScroll;

    double _viewStartTime;
    double _viewDuration;
    double _playbackTime;
    bool _trackPlayback;

    int m_frame;

    bool _showFps;
    QElapsedTimer _fpsTimer;
    int _lastFpsFrame;
};

#endif
