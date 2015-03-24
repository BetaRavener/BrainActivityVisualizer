#ifndef FOURIER_TRANSFORM_H
#define FOURIER_TRANSFORM_H

#include <memory>

#include "kiss_fftr.h"
#include "signalData.h"
#include "spectrum.h"

class FourierTransform
{
public:
    FourierTransform();
    ~FourierTransform();

    void init(int length);
    Spectrum::Ptr process(SignalData::PtrConst signal, int startIdx = -1);

private:
    float compAbs(kiss_fft_cpx x);

    kiss_fftr_cfg _configuration;
    int _length;
};

#endif
