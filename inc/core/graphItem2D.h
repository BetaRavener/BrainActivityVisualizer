// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef GRAPH_ITEM_2D_H
#define GRAPH_ITEM_2D_H

#include <vector>

#include <UniShader/UniShader.h>
#include <glm/common.hpp>
#include <signalRecord.h>

/**
 * @brief The GraphItem2D class represents a single signal chart.
 */
class GraphItem2D
{
public:
    GraphItem2D(SignalData::WeakPtrConst _signalData);

    /**
     * @brief Getter.
     * @return Number of samples stored by this item.
     */
    unsigned int valueCount() const;

    /**
     * @brief Getter.
     * @return OpenGL buffer with samples.
     */
    us::Buffer<float>::Ptr positions() const;

    /**
     * @brief Getter.
     * @return OpenGL buffer with indices of the samples.
     */
    us::Buffer<unsigned int>::Ptr indices() const;

    /**
     * @brief Getter.
     * @return Item's vertical zoom.
     */
    float verticalZoom() const;

    /**
     * @brief Setter.
     * @param zoom New vertical zoom for the item.
     */
    void verticalZoom(float zoom);

    /**
     * @brief Getter.
     * @return Spacing between the samples.
     */
    float sampleSpacing() const;

    //void setData(float horizontalZoom, unsigned int middleSample, unsigned int width);

    /**
     * @brief Getter.
     * @return Pointer to SignalData associated with this item.
     */
    SignalData::WeakPtrConst signalData() const;

    /**
     * @brief Sets the data displayed by the item.
     * @param startTime The first moment displayed by the item.
     * @param endTime The last moment displayed by the item.
     * @param width Width of the item.
     * @param clearCache If true, the cache will be rebuilt even if available.
     */
    void setData(double startTime, double endTime, unsigned int width, bool clearCache = false);

private:
    void buildCache(unsigned int horizontalZoom, bool clearCache = false);
    void updateIndices(unsigned int previousValueCount);

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
