// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "fourierTransform.h"

#include <algorithm>
#include <stdexcept>
#include <math.h>

#include "hammingWindow.h"

FourierTransform::FourierTransform() :
    _window(0),
    _configuration(nullptr),
    _length(0)
{
}

FourierTransform::~FourierTransform()
{
    if (_configuration)
        kiss_fftr_free(_configuration);
}

void FourierTransform::init(int length)
{
    _length = length;
    _window = HammingWindow(_length);
    _configuration = kiss_fftr_alloc(length, 0, NULL, NULL);
}

Spectrum::Ptr FourierTransform::process(SignalData::WeakPtr signal, unsigned int centerIdx)
{
    const auto& data = signal->data();

    if (centerIdx + _length > data.size())
        throw std::runtime_error("Not enough samples for FFT");

    std::vector<kiss_fft_cpx> result;
    std::vector<float> input;
    std::vector<double> output;
    double resolution = signal->samplingFreq() / _length;

    input.resize(_length);
    result.resize(_length / 2 + 1);
    output.resize(result.size());

    for (unsigned int i = 0; i < input.size(); i++)
        input[i] = signal->data()[centerIdx + i];

    _window.applyTo(input);

    kiss_fftr(_configuration, &input[0], &result[0]);

    for (unsigned int i = 0; i < result.size(); i++)
        output[i] = normalize(compAbs(result[i]));

    return Spectrum::create(std::move(output), resolution, signal->maxAmplitude());
}

Spectrum::Ptr FourierTransform::process(SignalData::WeakPtr signal)
{
    return process(signal, signal->data().size() - _length);
}

float FourierTransform::compAbs(kiss_fft_cpx x)
{
    return sqrtf(x.i * x.i + x.r * x.r);
}

float FourierTransform::normalize(float x)
{
    return x / _length;
}

