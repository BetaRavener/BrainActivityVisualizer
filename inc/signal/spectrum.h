#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <memory>
#include <vector>

class Spectrum
{
public:
    typedef std::shared_ptr<Spectrum> Ptr;
    typedef std::shared_ptr<const Spectrum> PtrConst;

    static Ptr create(std::vector<double> data, double resolution, double amplitude);

    double maxFrequency();
    double resolution();
    double amplitude();

    double normalize(double x);

    unsigned int getIdxAtFreq(double freq);

    double mean(double beginFreq, double endFreq);

    double max(double beginFreq, double endFreq);
private:
    Spectrum();

    std::vector<double> _data;
    double _resolution;
    double _amplitude;
};

#endif
