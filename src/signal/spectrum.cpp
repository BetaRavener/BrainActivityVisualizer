#include "spectrum.h"
#include <glm/common.hpp>

Spectrum::Ptr Spectrum::create(std::vector<double> data, double resolution, double amplitude)
{
    Ptr ptr(new Spectrum);
    ptr->_data = std::move(data);
    ptr->_resolution = resolution;
    ptr->_amplitude = amplitude;
    return ptr;
}

double Spectrum::maxFrequency()
{
    // Subtract 1 because there is bin with 0 Hz
    return (_data.size() - 1) * _resolution;
}

double Spectrum::resolution()
{
    return _resolution;
}

double Spectrum::amplitude()
{
    return _amplitude;
}

double Spectrum::normalize(double x)
{
    return x / _amplitude;
}

unsigned int Spectrum::getIdxAtFreq(double freq)
{
    return static_cast<unsigned int>(freq / _resolution);
}

double Spectrum::mean(double beginFreq, double endFreq)
{
    unsigned int beginIdx = getIdxAtFreq(beginFreq);
    unsigned int endIdx = getIdxAtFreq(endFreq);

    if (beginIdx >= endIdx)
        return 0.0;

    double mean = 0.0;
    for (unsigned int i = beginIdx; i <= endIdx; i++)
    {
        mean += _data[i];
    }

    return mean / (endIdx - beginIdx);
}

double Spectrum::max(double beginFreq, double endFreq)
{
    unsigned int beginIdx = getIdxAtFreq(beginFreq);
    unsigned int endIdx = getIdxAtFreq(endFreq);

    if (beginIdx >= endIdx)
        return 0.0;

    double max = 0.0;
    for (unsigned int i = beginIdx; i <= endIdx; i++)
    {
        max = glm::max(max, _data[i]);
    }

    return max;
}

Spectrum::Spectrum()
{

}
