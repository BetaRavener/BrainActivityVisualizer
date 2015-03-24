#include "fourierTransform.h"

#include <algorithm>
#include <stdexcept>
#include <math.h>

FourierTransform::FourierTransform() :
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
    _configuration = kiss_fftr_alloc(length, 0, NULL, NULL);
}

Spectrum::Ptr FourierTransform::process(SignalData::PtrConst signal, int startIdx)
{
    const auto& data = signal->data();

    if (startIdx == -1)
        startIdx = data.size() - _length;
    else if (startIdx + _length > data.size())
        throw std::runtime_error("Not enough samples for FFT");

    std::vector<kiss_fft_cpx> result;
    std::vector<float> input;
    std::vector<double> output;
    double resolution = signal->samplingFreq() / 2.;

    input.resize(_length);
    result.resize(_length / 2 + 1);
    output.resize(result.size());

    for (unsigned int i = 0; i < result.size(); i++)
        input[i] = signal->data()[startIdx + i];

    kiss_fftr(_configuration, &input[0], &result[0]);

    for (unsigned int i = 0; i < result.size(); i++)
        output[i] = compAbs(result[i]);

    return Spectrum::create(std::move(output), resolution);
}

float FourierTransform::compAbs(kiss_fft_cpx x)
{
    return sqrtf(x.i * x.i + x.r * x.r);
}

