// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "graphItem2D.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>

GraphItem2D::GraphItem2D(SignalData::WeakPtrConst signalData) :
    _valueCount(0),
    _posAttrBuf(us::Buffer<float>::create()),
    _indicesBuf(us::Buffer<unsigned int>::create()),
    _signalData(signalData),
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

float GraphItem2D::sampleSpacing() const
{
    return _sampleSpacing;
}

SignalData::WeakPtrConst GraphItem2D::signalData() const
{
    return _signalData;
}

void GraphItem2D::buildCache(unsigned int horizontalZoom, bool clearCache)
{
    if (!clearCache && _cacheZoom == horizontalZoom)
        return;

    _cache.clear();
    const auto& data = _signalData->data();
    unsigned int dataSampleCount = _signalData->sampleCount();
    unsigned int binSize = 1;
    for (unsigned int i = 0; i < horizontalZoom; i++)
        binSize *= 2;

    for (unsigned int i = 0; i < dataSampleCount / binSize; i++)
    {
        unsigned int binIdx = i * binSize;

        if (binIdx >= dataSampleCount)
            break;

        float min, max;
        min = max = data[binIdx];

        for (unsigned int j = 1; j < binSize; j++)
        {
            unsigned int sampleIdx = binIdx + j;
            if (sampleIdx >= dataSampleCount)
                break;

            float val = data[sampleIdx];
            min = val < min ? val : min;
            max = val > max ? val : max;
        }

        _cache.push_back(min);
        _cache.push_back(max);
    }

    _cacheZoom = horizontalZoom;
}

void GraphItem2D::updateIndices(unsigned int previousValueCount)
{
    if (previousValueCount == _valueCount)
        return;

    if (_valueCount > 0)
    {
        std::vector<unsigned int> indices;
        indices.push_back(0);
        for (unsigned int i = 0; i < _valueCount; i++)
            indices.push_back(i);
        indices.push_back(_valueCount - 1);
        _indicesBuf->setData(indices);
    }
}

void GraphItem2D::setData(double startTime, double endTime, unsigned int width, bool clearCache)
{
    // Add 1 sample because we need to form N lines, which are defined by N+1 points
    const auto& data = _signalData->data();

    unsigned int previousValueCount = _valueCount;
    unsigned int firstSample = _signalData->getIdxAtTime(startTime);
    unsigned int lastSample = _signalData->getIdxAtTime(endTime);
    unsigned int samplesCount = lastSample - firstSample;
    double samplesPerPixel = (double)samplesCount / (double)width;
    unsigned int zoom = 0;
    while (samplesPerPixel >= 2.0)
    {
        firstSample /= 2.0;
        lastSample /= 2.0;
        samplesPerPixel /= 2.0;
        zoom++;
    }

    _sampleSpacing = 1.0 / samplesPerPixel;

    std::vector<float> reducedData;
    if (zoom > 0)
    {
        buildCache(zoom, clearCache);
        // Divide by 2 beacause cache contains 2 values - min and max
        _sampleSpacing *= 0.5;

        _valueCount = 0;
        // Because of half spacing, increase the window width by 2
        for (unsigned int i = 0; i < width * 2; i++)
        {
            int bin = i + firstSample;
            reducedData.push_back(_cache[bin*2]);
            reducedData.push_back(_cache[bin*2 + 1]);
            _valueCount += 2;
        }

        if (_valueCount > 0)
            _posAttrBuf->setData(reducedData);
    }
    else
    {
        _valueCount = samplesCount;
        for (unsigned int i = 0; i < _valueCount; i++)
            reducedData.push_back(data[firstSample + i]);

        if (_valueCount > 0)
            _posAttrBuf->setData(reducedData);
    }

    updateIndices(previousValueCount);
}
