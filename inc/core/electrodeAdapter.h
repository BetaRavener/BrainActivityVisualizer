// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef ELECTRODEADAPTER_H
#define ELECTRODEADAPTER_H

#include "signalBatch.h"

/**
 * @brief The ElectrodeAdapter class binds signals to electrodes and determines
 * how the signal values will be visualized
 */
class ElectrodeAdapter
{
public:
    ElectrodeAdapter();
    ~ElectrodeAdapter();

    /**
     * @brief init Initializes the adapter.
     * @param batch Batch of signals that represent input to the adapter.
     */
    void init(SignalBatch::WeakPtr batch);

    /**
     * @brief Setter.
     * @param time Current animation time.
     */
    void setTime(double time);

    /**
     * @brief Getter.
     * @return Signal gain.
     */
    double gain();

    /**
     * @brief Setter.
     * @param Signal gain.
     */
    void gain(double gain);

    enum class TransformationType{None, FFT};

    /**
     * @brief Getter.
     * @return Type of transformation that is used for signal visualziation.
     */
    TransformationType transformationType();

    /**
     * @brief Setter.
     * @param type Type of transformation that is used for signal visualziation.
     */
    void transformationType(TransformationType type);

    /**
     * @brief Getter.
     * @return The beginning of frequency range if the transformation type is different from None.
     */
    double transformationBeginFreq();

    /**
     * @brief Setter.
     * @param freq The beginning of frequency range if the transformation type is different from None.
     */
    void transformationBeginFreq(double freq);

    /**
     * @brief Getter.
     * @return The end of frequency range if the transformation type is different from None.
     */
    double transformationEndFreq();

    /**
     * @brief Setter.
     * @param freq The end of frequency range if the transformation type is different from None.
     */
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
