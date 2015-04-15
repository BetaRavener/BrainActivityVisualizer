#include "highpassFilter.h"
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

HighpassFilter::HighpassFilter(unsigned int halfLength, double cutoffFreq, double samplingFreq) :
    SignalFilter(halfLength)
{
    double sum = 0.0;
    double angularCutoff = 2 * glm::pi<double>() * cutoffFreq / samplingFreq;
    for (unsigned int i = 0; i < _length; i++)
    {
        if (i == halfLength)
        {
            _impulseResponse[i] = 1 - angularCutoff / glm::pi<double>();
        }
        else
        {
            double causalIdx = (((double)i) - halfLength);
            _impulseResponse[i] = -glm::sin(angularCutoff * causalIdx) /
                                  (glm::pi<double>() * causalIdx);
        }
        sum += glm::abs(_impulseResponse[i]);
    }

    // Normalize the coefficients to maintain the average of signal
    for (unsigned int i = 0; i < _length; i++)
    {
        _impulseResponse[i] /= sum;
    }
}

HighpassFilter::~HighpassFilter()
{

}

