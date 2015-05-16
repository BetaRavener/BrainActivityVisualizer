// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef FOURIER_TRANSFORM_H
#define FOURIER_TRANSFORM_H

#include <memory>

#include "kiss_fftr.h"
#include "signalData.h"
#include "spectrum.h"
#include "hammingWindow.h"

/**
 * @brief The FourierTransform class provides a wrapper arround KissFFT library.
 */
class FourierTransform
{
public:
    FourierTransform();
    ~FourierTransform();

    /**
     * @brief Initalizes FFT before usage.
     * @param length The length of FFT.
     */
    void init(int length);

    /**
     * @brief Performs FFT at the specified index.
     * @param signal Signal to process.
     * @param centerIdx Index where FFT will be performed.
     * @return Spectrum of the signal.
     */
    Spectrum::Ptr process(SignalData::WeakPtr signal, unsigned int centerIdx);

    // Runs FFT at the end of signal
    /**
     * @brief Performs FFT at the end of a signal.
     * @param signal Signal to process.
     * @return Spectrum of the signal.
     */
    Spectrum::Ptr process(SignalData::WeakPtr signal);
private:
    float compAbs(kiss_fft_cpx x);
    float normalize(float x);

    HammingWindow _window;
    kiss_fftr_cfg _configuration;
    int _length;
};

#endif
