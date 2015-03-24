#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <memory>
#include <vector>

class Spectrum
{
public:
    typedef std::shared_ptr<Spectrum> Ptr;
    typedef std::shared_ptr<const Spectrum> PtrConst;

    static Ptr create(std::vector<double> data, double resolution);

    double maxFrequency();
    double resolution();

private:
    Spectrum(std::vector<double> data, double resolution);

    std::vector<double> _data;
    double _resolution;
};

#endif
