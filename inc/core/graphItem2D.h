#ifndef GRAPH_ITEM_2D_H
#define GRAPH_ITEM_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>
#include <signalRecord.h>

class GraphItem2D
{
public:
    GraphItem2D(SignalData::WeakPtrConst _signalData);

    unsigned int valueCount() const;
    us::Buffer<float>::Ptr positions() const;
    us::Buffer<unsigned int>::Ptr indices() const;

    float verticalZoom() const;
    void verticalZoom(float zoom);

    float sampleSpacing() const;

    //void setData(float horizontalZoom, unsigned int middleSample, unsigned int width);

    SignalData::WeakPtrConst signalData() const;
    void setData(double startTime, double endTime, unsigned int width, bool clearCache = false);
private:
    void buildCache(unsigned int horizontalZoom, bool clearCache = false);

    unsigned int _valueCount;

    // Buffers
    us::Buffer<float>::Ptr _posAttrBuf;
    us::Buffer<unsigned int>::Ptr _indicesBuf;

    SignalData::WeakPtrConst _signalData;
    float _verticalZoom;

    std::vector<float> _cache;
    float _cacheZoom;

    float _sampleSpacing;
};

#endif
