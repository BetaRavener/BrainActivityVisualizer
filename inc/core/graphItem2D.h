#ifndef GRAPH_ITEM_2D_H
#define GRAPH_ITEM_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>
#include <signalRecord.h>

class GraphItem2D
{
public:
    GraphItem2D(SignalRecord* signalRecord);

    unsigned int valueCount() const;
    us::Buffer<float>::Ptr positions() const;
    us::Buffer<unsigned int>::Ptr indices() const;

    float verticalZoom() const;
    void verticalZoom(float zoom);

    float minHorizontalZoom(unsigned int width);

    void setData(float horizontalZoom, unsigned int middleSample, unsigned int width);

    int dataSampleCount();

    const SignalRecord* signalRecord();
private:
    void buildCache(float horizontalZoom);

    unsigned int _valueCount;

    // Buffers
    us::Buffer<float>::Ptr _posAttrBuf;
    us::Buffer<unsigned int>::Ptr _indicesBuf;

    SignalRecord* _signalRecord;
    float _verticalZoom;

    std::vector<float> _cache;
    float _cacheZoom;
};

#endif
