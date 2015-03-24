#ifndef GRAPH_VIEW_2D
#define GRAPH_VIEW_2D

#include "openglwidget.h"

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
#include "graphGrid2D.h"

class GraphView2D : public OpenGLWidget
{
    Q_OBJECT

public:
    GraphView2D(QWidget *parrent = 0);
    ~GraphView2D();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    void electrodeMap(ElectrodeMap* electrodeMap);
    void addScrollBars(QScrollBar* horizontal, QScrollBar* vertical);
    void addLabels(QLayout* horizontal, QLayout* vertical);

private slots:
    void open();
    void dialogOk();

    void horizontallyScrolled(int value);
    void verticallyScrolled(int value);

private:
    void updateData();
    void updateScrollBars();
    void updateLabels();
    void checkZoom();

    ElectrodeMap* _electrodeMap;
    std::vector<GraphItem2D> _items;

    QMenu _menu;
    OpenSignalFileDialog _dialog;

    GraphGrid2D* _graphGrid;
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

    int m_frame;

    bool _showFps;
    QElapsedTimer _fpsTimer;
    int _lastFpsFrame;
};

#endif
