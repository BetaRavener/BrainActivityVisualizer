#include "graphView2D.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QLayoutItem>
#include <QLabel>

#include <utility>
#include <iostream>
#include <string>
#include <random>

#include <glm/gtc/matrix_transform.hpp>
#include <glmHelpers.h>

GraphView2D::GraphView2D(QWidget *parrent) :
    OpenGLWidget(parrent),
    _horizontalScrollMultiplier(1000.0),
    _shapeRenderer(nullptr),
    _graphRenderer(nullptr),
    _horizontalScrollBar(nullptr),
    _verticalScrollBar(nullptr),
    _horizontalLabels(nullptr),
    _verticalLabels(nullptr),
    _zoom(1.f, 1.f),
    _middleSample(0),
    _verticalScroll(0),
    _updatingScroll(false),
    _viewStartTime(0.0),
    _viewDuration(10.0),
    _playbackTime(0.0),
    m_frame(0),
    _showFps(false)
{
}

GraphView2D::~GraphView2D()
{
    activateGL();
    _items.clear();

    delete _shapeRenderer;
    _shapeRenderer = nullptr;

    delete _graphRenderer;
    _graphRenderer = nullptr;

    deactivateGL();
}

void GraphView2D::initialize()
{
    installEventFilter(this);

    _shapeRenderer = new ShapeRenderer2D();
    _graphRenderer = new GraphRenderer2D();

    _shapeRenderer->init();
    _graphRenderer->init();

    _middleSample = width() / 2;

    QAction* openAct = new QAction("Open...", this);
    //connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    _menu.addAction(openAct);
    _menu.addSeparator();
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

    _shapeRenderer->update(matrix);
    _graphRenderer->update(matrix);

    prepareGrid();
    prepareBackground();

    if (_graphBackgroundCount > 0)
    {
        _shapeRenderer->setPositions(_graphBackground);
        _shapeRenderer->setColors(_graphBackgroundColor);
        _shapeRenderer->render(us::PrimitiveType::TRIANGLES, _graphBackgroundCount);
    }

    if (_graphGridCount > 0)
    {
        _shapeRenderer->setPositions(_graphGrid);
        _shapeRenderer->setColors(_graphGridColor);
        _shapeRenderer->render(us::PrimitiveType::LINES, _graphGridCount);
    }

    //TODO: Use horizontalSeparators (must return firstItemIdx)
    glm::vec2 size = itemSize();
    glm::vec2 position(0.f, height() + _verticalScroll);
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
    if (event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons().testFlag(Qt::RightButton))
        {
            double time = _viewStartTime + (double)mouseEvent->pos().x() / width() * _viewDuration;
            emit requestTime(time);
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
                _viewDuration *= numSteps.y() > 0 ? 2.f : 0.5f;
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

            checkZoom();
            checkView();
            if (needDataReset)
                updateData();
            updateScrollBars();
            updateLabels();
            update();
        }
    }
    if (event->type() == QEvent::Resize)
    {
        checkZoom();
        checkView();
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

    updateScrollBars();

    connect(_horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horizontallyScrolled(int)));
    connect(_verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(verticallyScrolled(int)));

}

void GraphView2D::addLabels(QLayout *horizontal, QLayout *vertical)
{
    _horizontalLabels = horizontal;
    _verticalLabels = vertical;

    updateLabels();
}

void GraphView2D::signalBatch(SignalBatch::WeakPtr signalBatch)
{
    activateGL();
    _items.clear();
    deactivateGL();

    _signalBatch = signalBatch;
    _minZoom = glm::vec2(0.f, 0.f);
    std::vector<SignalData::Ptr> dataSignals;
    for (SignalData::Ptr signalData : signalBatch->dataSignals())
    {
        activateGL();
        _items.push_back(GraphItem2D(SignalData::WeakPtrConst(signalData)));
        dataSignals.push_back(signalData);
        deactivateGL();
    }

    checkZoom();
    checkView();
    updateData();
    updateLabels();
    updateScrollBars();
    update();
}

void GraphView2D::timeChanged(double time)
{
    _playbackTime = time;
    repaint();
}

void GraphView2D::dataChanged()
{
    checkZoom();
    checkView();
    updateData(true);
    updateLabels();
    updateScrollBars();
    update();
}

void GraphView2D::horizontallyScrolled(int value)
{
    if (_updatingScroll)
        return;

    _viewStartTime = (double)value / _horizontalScrollMultiplier;

    updateData();
    update();
}

void GraphView2D::verticallyScrolled(int value)
{
    if (_updatingScroll)
        return;

    _verticalScroll = value;
    update();
}

void GraphView2D::updateData(bool clearCache)
{
    activateGL();
    for (GraphItem2D& item : _items)
        item.setData(_viewStartTime, _viewStartTime + _viewDuration, width(), clearCache);
    deactivateGL();
}

void GraphView2D::updateScrollBars()
{
    // Set this to prevent double update caused
    // by signal emited by setValue
    _updatingScroll = true;

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
            _horizontalScrollBar->setMaximum((_signalBatch->duration() - _viewDuration) * _horizontalScrollMultiplier);
            _horizontalScrollBar->setValue(_viewStartTime * _horizontalScrollMultiplier);
            _horizontalScrollBar->setPageStep(_viewDuration * _horizontalScrollMultiplier);
        }
    }

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
            _verticalScrollBar->setMaximum(maxVericallScroll());
            _verticalScrollBar->setValue(_verticalScroll);
            _verticalScrollBar->setPageStep(height());
        }
    }

    _updatingScroll = false;
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
            QLabel* label = new QLabel(QString::fromStdString(item.signalData()->label()));
            label->setFixedSize(QSize(100, itemSize().y));
            label->setStyleSheet("border: 1px solid grey");
            _verticalLabels->addWidget(label);
            label->show();
        }
    }
}

void GraphView2D::checkZoom()
{
    if(!_signalBatch)
        return;

    _minZoom.x = _signalBatch->maxResolution() * width();
    _minZoom.y = _items.size() > 0 ? 1.f / _items.size() : 0.f;
    _maxZoom.x = _signalBatch->duration();
    //_maxZoom.y = glm::max(1.f, glm::ceil((float)height() * _zoom.y) * _items.size() / (float)height());
    _maxZoom.y = 1.f;
    // Min zoom is all samples on screen
    _viewDuration = glm::max(_viewDuration, (double)_minZoom.x);
    // Max zoom is one sample on screen
    _viewDuration = glm::min(_viewDuration, (double)_maxZoom.x);
    // Min zoom is all items on screen
    _zoom.y = glm::max(_zoom.y, _minZoom.y);
    // Max zoom is one item on screen
    _zoom.y = glm::min(_zoom.y, _maxZoom.y);
}

void GraphView2D::checkView()
{
    if (_signalBatch)
        _viewStartTime = glm::min(_viewStartTime, _signalBatch->duration() - _viewDuration);
    _verticalScroll = glm::min(_verticalScroll, maxVericallScroll());
    _verticalScroll = glm::max(_verticalScroll, 0);
}

int GraphView2D::maxVericallScroll()
{
    return (int)(itemSize().y * _items.size() - height());
}

std::vector<float> GraphView2D::horizontalSeparators()
{
    glm::vec2 size = itemSize();
    glm::vec2 position(0.f, height() + _verticalScroll);

    std::vector<float> horizontal;
    for (unsigned int i = 0; i < _items.size(); i++)
    {
        position.y -= size.y;
        if (position.y > height() + size.y)
            continue;

        if (position.y < -size.y)
            break;

        horizontal.push_back(position.y);
    }

    return std::move(horizontal);
}

void GraphView2D::prepareBackground(glm::vec3 firstColor, glm::vec3 secondColor)
{
    _graphBackground.clear();
    _graphBackgroundColor.clear();
    _graphBackgroundCount = 0;

    glm::vec2 size = itemSize();
    glm::vec2 topLeft = glm::vec2(0.f, height() + _verticalScroll), bottomRight;
    for (unsigned int i = 0; i < _items.size(); i++, topLeft.y -= size.y)
    {
        if (topLeft.y > height() + size.y)
            continue;

        if (topLeft.y < -size.y)
            break;

        bottomRight = glm::vec2(width(), topLeft.y - size.y);

        glm::Helpers::pushBack(_graphBackground, topLeft);
        glm::Helpers::pushBack(_graphBackground, glm::vec2(bottomRight.x, topLeft.y));
        glm::Helpers::pushBack(_graphBackground, glm::vec2(bottomRight));
        glm::Helpers::pushBack(_graphBackground, topLeft);
        glm::Helpers::pushBack(_graphBackground, glm::vec2(topLeft.x, bottomRight.y));
        glm::Helpers::pushBack(_graphBackground, glm::vec2(bottomRight));

        // Alternate two colors
        for (int j = 0; j < 6; j++)
            glm::Helpers::pushBack(_graphBackgroundColor, (i % 2 == 0 ? firstColor : secondColor));

        _graphBackgroundCount += 6;
    }
}

void GraphView2D::prepareGrid(glm::vec3 color, glm::vec3 timeColor)
{
    std::vector<float> horizontal, vertical;

    horizontal = std::move(horizontalSeparators());
    for (int i = 0; i < width(); i += width() / 10)
        vertical.push_back(i);

    _graphGrid.clear();
    _graphGridColor.clear();
    _graphGridCount = 0;

    for (auto y : horizontal)
    {
        glm::Helpers::pushBack(_graphGrid, glm::vec2(0, y));
        glm::Helpers::pushBack(_graphGridColor, color);
        glm::Helpers::pushBack(_graphGrid, glm::vec2(width(), y));
        glm::Helpers::pushBack(_graphGridColor, color);
        _graphGridCount += 2;
    }

    for (auto x : vertical)
    {
        glm::Helpers::pushBack(_graphGrid, glm::vec2(x, 0));
        glm::Helpers::pushBack(_graphGridColor, color);
        glm::Helpers::pushBack(_graphGrid, glm::vec2(x, height()));
        glm::Helpers::pushBack(_graphGridColor, color);
        _graphGridCount += 2;
    }

    double timeX = (_playbackTime - _viewStartTime) / _viewDuration;
    if (timeX > 0.0 && timeX < 1.0)
    {
        timeX *= width();
        glm::Helpers::pushBack(_graphGrid, glm::vec2(timeX, 0));
        glm::Helpers::pushBack(_graphGridColor, timeColor);
        glm::Helpers::pushBack(_graphGrid, glm::vec2(timeX, height()));
        glm::Helpers::pushBack(_graphGridColor, timeColor);
        _graphGridCount += 2;
    }
}

glm::vec2 GraphView2D::itemSize()
{
    return glm::vec2(width(), glm::ceil((float)height() * _zoom.y));
}
