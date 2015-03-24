#include "graphItem2D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

GraphItem2D::GraphItem2D(SignalRecord *signalRecord) :
    _valueCount(0),
    _posAttrBuf(us::Buffer<float>::create()),
    _indicesBuf(us::Buffer<unsigned int>::create()),
    _signalRecord(signalRecord),
    _verticalZoom(1.f)
{

}

unsigned int GraphItem2D::valueCount() const
{
    return _valueCount;
}

us::Buffer<float>::Ptr GraphItem2D::positions() const
{
    return _posAttrBuf;
}

us::Buffer<unsigned int>::Ptr GraphItem2D::indices() const
{
    return _indicesBuf;
}

float GraphItem2D::verticalZoom() const
{
    return _verticalZoom;
}

void GraphItem2D::verticalZoom(float zoom)
{
    _verticalZoom = zoom;
}

float GraphItem2D::minHorizontalZoom(unsigned int width)
{
    return 1.f / ((float)_signalRecord->data()->sampleCount() / width);
}

int GraphItem2D::dataSampleCount()
{
    return _signalRecord->data()->sampleCount();
}

const SignalRecord *GraphItem2D::signalRecord()
{
    return _signalRecord;
}

void GraphItem2D::buildCache(float horizontalZoom)
{
    if (_cacheZoom == horizontalZoom)
        return;

    _cache.clear();
    SignalData::PtrConst data = _signalRecord->data();
    unsigned int dataSampleCount = data->sampleCount();
    int binSize = 1 / horizontalZoom;

    for (int i = 0; i < dataSampleCount / binSize; i++)
    {
        int binIdx = i * binSize;

        if (binIdx >= dataSampleCount)
            break;

        float min, max;
        min = max = data->data()[binIdx];

        for (int j = 1; j < binSize; j++)
        {
            int idx = binIdx + j;
            if (idx >= dataSampleCount)
                break;

            float val = data->data()[idx];
            min = val < min ? val : min;
            max = val > max ? val : max;
        }

        _cache.push_back(min);
        _cache.push_back(max);
    }

    _cacheZoom = horizontalZoom;
}

void GraphItem2D::setData(float horizontalZoom, unsigned int middleSample, unsigned int width)
{
    SignalData::PtrConst data = _signalRecord->data();

    // Add 1 sample because we need to form N lines, which are defined by N+1 points
    unsigned int samplesInWindow = glm::ceil(width / horizontalZoom) + 1;
    unsigned int leftEdge = 0;
    if (middleSample > samplesInWindow / 2)
        leftEdge = middleSample - samplesInWindow / 2;

    if (leftEdge > data->sampleCount() - samplesInWindow)
        leftEdge = data->sampleCount() - samplesInWindow;

    int binSize = 1 / horizontalZoom;

    std::vector<float> reducedData;
    if (binSize > 1)
    {
        buildCache(horizontalZoom);
        _valueCount = 0;
        for (int i = 0; i < width; i++)
        {
            int bin = i + leftEdge / binSize;
            reducedData.push_back(_cache[bin*2]);
            reducedData.push_back(_cache[bin*2 + 1]);
            _valueCount += 2;
        }

        if (_valueCount > 0)
            _posAttrBuf->setData(reducedData);
    }
    else
    {
        _valueCount = samplesInWindow;
        _valueCount = glm::min(_valueCount, data->sampleCount() - leftEdge);
        for (int i = 0; i < _valueCount; i++)
            reducedData.push_back(data->data()[leftEdge + i]);

        if (_valueCount > 0)
            _posAttrBuf->setData(reducedData);
    }

    if (_valueCount > 0)
    {
        std::vector<unsigned int> indices;
        indices.push_back(0);
        for (int i = 0; i < _valueCount; i++)
            indices.push_back(i);
        indices.push_back(_valueCount - 1);
        _indicesBuf->setData(indices);
    }
}
