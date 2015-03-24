#include "spectrum.h"

Spectrum::Spectrum(std::vector<double> data, double resolution) :
    _data(data),
    _resolution(resolution)
{

}

Spectrum::Ptr Spectrum::create(std::vector<double> data, double resolution)
{
    return Ptr(new Spectrum(data, resolution));
}

double Spectrum::maxFrequency()
{
    return (_data.size() - 1) * _resolution;
}

double Spectrum::resolution()
{
    return _resolution;
}
