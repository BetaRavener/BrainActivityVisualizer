#include "graphView2D.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QLayoutItem>
#include <QLabel>

#include <iostream>
#include <string>
#include <random>

#include <glm/gtc/matrix_transform.hpp>

GraphView2D::GraphView2D(QWidget *parrent) :
    OpenGLWidget(parrent),
    _electrodeMap(nullptr),
    _zoom(1.f, 1.f),
    _middleSample(0),
    _verticalScroll(0),
    m_frame(0),
    _showFps(false),
    _graphGrid(nullptr),
    _graphRenderer(nullptr),
    _horizontalScrollBar(nullptr),
    _verticalScrollBar(nullptr),
    _horizontalLabels(nullptr),
    _verticalLabels(nullptr)
{
}

GraphView2D::~GraphView2D()
{
    activateGL();
    _items.clear();
    deactivateGL();
}

void GraphView2D::initialize()
{
    installEventFilter(this);

    _graphGrid = new GraphGrid2D();
    _graphGrid->init();

    _graphRenderer = new GraphRenderer2D();
    _graphRenderer->init();

    _middleSample = width() / 2;

    QAction* openAct = new QAction("Open...", this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    _menu.addAction(openAct);
    _menu.addSeparator();

    _dialog.setModal(true);
    connect(&_dialog, SIGNAL(accepted()), this, SLOT(dialogOk()));
}

void GraphView2D::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glEnable(GL_MULTISAMPLE);

    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 projMatrix = glm::ortho(0.f, (float)width(), 0.f, (float)height());
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 matrix = projMatrix * modelViewMatrix;

    _graphGrid->update(matrix);
    _graphRenderer->update(matrix);

    glm::vec2 size(width(), glm::ceil((float)height() * _zoom.y));
    glm::vec2 position(0.f, height() + _verticalScroll);

    std::vector<float> horizontalLines, verticalLines;

    for (unsigned int i = 0; i < _items.size(); i++)
    {
        position.y -= size.y;
        if (position.y > height() + size.y)
            continue;

        if (position.y < -size.y)
            break;

        horizontalLines.push_back(position.y);
    }

    for (int i = 0; i < width(); i += width() / 10)
        verticalLines.push_back(i);

    _graphGrid->setGrid(horizontalLines, verticalLines, glm::vec2(width(), height()));
    _graphGrid->render();

    position = glm::vec2(0.f, height() + _verticalScroll);
    for (unsigned int i = 0; i < _items.size(); i++)
    {
        position.y -= size.y;
        if (position.y > height() + size.y)
            continue;

        if (position.y < -size.y)
            break;
        _graphRenderer->renderItem(_items[i], _zoom, position, size);
    }

    glDisable(GL_MULTISAMPLE);

    ++m_frame;

    if (_showFps)
    {
        qint64 elapsed = _fpsTimer.elapsed();
        if (elapsed > 1000)
        {
            double fps = (double)(m_frame - _lastFpsFrame) / elapsed * 1000.0;
            std::cout << fps << std::endl;
            _lastFpsFrame = m_frame;
            _fpsTimer.restart();
        }
    }
}

bool GraphView2D::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_F)
        {
            _showFps = !_showFps;
            if (_showFps)
            {
                _lastFpsFrame = m_frame;
                _fpsTimer.start();
            }
            else
            {
                _fpsTimer.invalidate();
            }
        }
        else if (keyEvent->key() == Qt::Key_L)
        {
            activateGL();
            _graphRenderer->reloadShaders();
            deactivateGL();

            updateData();
        }
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons().testFlag(Qt::RightButton))
        {
            _menu.exec(mapToGlobal(mouseEvent->pos()));
        }
    }
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        if(!wheelEvent->angleDelta().isNull())
        {
            QPoint numDegrees = wheelEvent->angleDelta() / 8;
            QPoint numSteps = numDegrees / 15;

            bool needDataReset = false;
            if (wheelEvent->modifiers().testFlag(Qt::ControlModifier))
            {
                _zoom.x *= numSteps.y() > 0 ? 2.f : 0.5f;
                needDataReset = true;
            }
            else if (wheelEvent->modifiers().testFlag(Qt::ShiftModifier))
            {
                _zoom.y *= numSteps.y() > 0 ? 2.f : 0.5f;
            }
            else if (wheelEvent->modifiers().testFlag(Qt::AltModifier))
            {
                for (auto& item : _items)
                    item.verticalZoom(item.verticalZoom() * (numSteps.x() > 0 ? 2.f : 0.5f));
            }

            if (needDataReset)
                updateData();

            checkZoom();
            updateScrollBars();
            updateLabels();
            update();
        }
    }
    if (event->type() == QEvent::Resize)
    {
        checkZoom();
        updateData();
        updateLabels();
        updateScrollBars();
        update();
    }
    return false;
}

void GraphView2D::addScrollBars(QScrollBar *horizontal, QScrollBar *vertical)
{
    _horizontalScrollBar = horizontal;
    _verticalScrollBar = vertical;

    _horizontalScrollBar->setTracking(true);
    _verticalScrollBar->setTracking(true);

    connect(_horizontalScrollBar, SIGNAL(sliderMoved(int)), this, SLOT(horizontallyScrolled(int)));
    connect(_verticalScrollBar, SIGNAL(sliderMoved(int)), this, SLOT(verticallyScrolled(int)));

    updateScrollBars();
}

void GraphView2D::addLabels(QLayout *horizontal, QLayout *vertical)
{
    _horizontalLabels = horizontal;
    _verticalLabels = vertical;

    updateLabels();
}

void GraphView2D::open()
{
    _dialog.show();
}

void GraphView2D::dialogOk()
{
    activateGL();
    _items.clear();
    deactivateGL();

    _minZoom = glm::vec2(0.f, 0.f);
    const auto& dialogResult = _dialog.getResult();
    for (auto& pair : dialogResult)
    {
        SignalRecord* record = pair.second;
        record->load();

        if (pair.first != "")
        {
            _electrodeMap->electrode(pair.first).signal(record);
        }

        activateGL();
        _items.push_back(GraphItem2D(record));
        deactivateGL();
    }

    checkZoom();
    updateData();
    updateLabels();
    updateScrollBars();
    update();
}

void GraphView2D::horizontallyScrolled(int value)
{
    if (_zoom.x > 0.5f)
        _middleSample = value;
    else
        _middleSample = value / _zoom.x;

    updateData();
    update();
}

void GraphView2D::verticallyScrolled(int value)
{
    _verticalScroll = value;
    update();
}

void GraphView2D::updateData()
{
    activateGL();
    for (GraphItem2D& item : _items)
        item.setData(_zoom.x, _middleSample, width());
    deactivateGL();
}

void GraphView2D::updateScrollBars()
{
    if (_horizontalScrollBar)
    {
        if (_items.size() == 0)
        {
            _horizontalScrollBar->setMinimum(0);
            _horizontalScrollBar->setMaximum(0);
            _horizontalScrollBar->setValue(0);
        }
        else
        {
            _horizontalScrollBar->setMinimum(0);
            if (_zoom.x > 0.5f)
            {
                _horizontalScrollBar->setMaximum(_items[0].dataSampleCount() - width() / _zoom.x);
                _horizontalScrollBar->setValue(_middleSample);
                _horizontalScrollBar->setPageStep(width() / _zoom.x);
            }
            else
            {
                _horizontalScrollBar->setMaximum(_items[0].dataSampleCount() * _zoom.x);
                _horizontalScrollBar->setValue(_middleSample * _zoom.x);
                _horizontalScrollBar->setPageStep(width());
            }
        }
    }

    // Check that scroll is in limit
    int maxVertical = (int)(glm::ceil((float)height() * _zoom.y) * _items.size() - height());
    _verticalScroll = glm::min(_verticalScroll, maxVertical);

    if (_verticalScrollBar)
    {
        if (_items.size() == 0)
        {
            _verticalScrollBar->setMinimum(0);
            _verticalScrollBar->setMaximum(0);
            _verticalScrollBar->setValue(0);
        }
        else
        {
            _verticalScrollBar->setMinimum(0);
            _verticalScrollBar->setMaximum(maxVertical);
            _verticalScrollBar->setValue(_verticalScroll);
            _verticalScrollBar->setPageStep(height());
        }
    }
}

void GraphView2D::updateLabels()
{
    if (_horizontalLabels)
    {
        /*while ((child = _horizontalLabels->takeAt(0)) != 0)
            delete child;

        _horizontalLabels->*/
    }

    if (_verticalLabels)
    {
        while (_verticalLabels->count() > 0)
        {
            QLayoutItem* layoutItem = _verticalLabels->takeAt(0);
            if (layoutItem->widget() != nullptr)
                delete (layoutItem->widget());
            delete layoutItem;
        }

        for (GraphItem2D item : _items)
        {
            QLabel* label = new QLabel(QString::fromStdString(item.signalRecord()->label()));
            label->setFixedSize(QSize(100, glm::ceil((float)height() * _zoom.y)));
            label->setStyleSheet("border: 1px solid grey");
            _verticalLabels->addWidget(label);
            label->show();
        }
    }
}

void GraphView2D::checkZoom()
{
    _minZoom.x = _items.size() > 0 ? _items[0].minHorizontalZoom(width()) : 0.f;
    _minZoom.y = _items.size() > 0 ? 1.f / _items.size() : 0.f;
    _maxZoom.x = width();
    _maxZoom.y = glm::max(1.f, glm::ceil((float)height() * _zoom.y) * _items.size() / (float)height());
    // Min zoom is all samples on screen
    _zoom.x = glm::max(_zoom.x, _minZoom.x);
    // Max zoom is one sample on screen
    _zoom.x = glm::min(_zoom.x, _maxZoom.x);
    // Min zoom is all items on screen
    _zoom.y = glm::max(_zoom.y, _minZoom.y);
    // Max zoom is one item on screen
    _zoom.y = glm::min(_zoom.y, _maxZoom.y);
}
