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
    Spectrum::Ptr process(SignalData::WeakPtr signal, unsigned int startIdx);

    // Runs FFT at the end of signal
    Spectrum::Ptr process(SignalData::WeakPtr signal);
private:
    float compAbs(kiss_fft_cpx x);
    float normalize(float x);

    kiss_fftr_cfg _configuration;
    int _length;
};

#endif
