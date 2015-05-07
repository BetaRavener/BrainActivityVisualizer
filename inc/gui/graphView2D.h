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

class GraphView2D : public OpenGLWidget
{
    Q_OBJECT

signals:
    void requestTime(double time);

public:
    GraphView2D(QWidget *parrent = 0);
    ~GraphView2D();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    void electrodeMap(ElectrodeMap* electrodeMap);
    void addScrollBars(QScrollBar* horizontal, QScrollBar* vertical);
    void addLabels(QLayout* horizontal, QLayout* vertical);

    void signalBatch(SignalBatch::WeakPtr signalBatch);

public slots:
    void timeChanged(double time);
    void dataChanged();

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

    int m_frame;

    bool _showFps;
    QElapsedTimer _fpsTimer;
    int _lastFpsFrame;
};

#endif
