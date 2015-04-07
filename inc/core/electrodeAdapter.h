#ifndef ELECTRODEADAPTER_H
#define ELECTRODEADAPTER_H

#include "signalBatch.h"

class ElectrodeAdapter
{
public:
    ElectrodeAdapter();
    ~ElectrodeAdapter();

    void init(SignalBatch::WeakPtr batch);

    void setTime(double time);

    double gain();
    void gain(double gain);

    enum class TransformationType{None, FFT, DWT};

    TransformationType transformationType();
    void transformationType(TransformationType type);

    double transformationBeginFreq();
    void transformationBeginFreq(double freq);

    double transformationEndFreq();
    void transformationEndFreq(double freq);

private:
    void noTransformation(double time);
    void fftTransformation(double time, double resolution = 1);

    SignalBatch::WeakPtr _signalBatch;
    double _gain;

    TransformationType _transformationType;
    double _transformationBeginFreq;
    double _transformationEndFreq;

};

#endif // ELECTRODEADAPTER_H
