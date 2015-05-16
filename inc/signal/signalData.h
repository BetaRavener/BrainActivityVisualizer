// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef SIGNAL_DATA_H
#define SIGNAL_DATA_H

#include <memory>
#include <vector>
#include "safePtr.h"
#include "electrode.h"

/**
 * @brief The SignalData class represents the signal and its samples.
 */
class SignalData
{
public:
    typedef std::vector<double> Samples;
    typedef std::shared_ptr<SignalData> Ptr;
    typedef std::shared_ptr<const SignalData> PtrConst;
    typedef SafePtr<SignalData> WeakPtr;
    typedef SafePtr<const SignalData> WeakPtrConst;

    static Ptr create();

    /**
     * @brief Creates new signal.
     * @param samples Samples of the signal.
     * @param freq Sampling frequency of the signal.
     * @param label Label of the signal.
     * @param electrode Electrode associated with the signal.
     * @return The new signal.
     */
    static Ptr create(Samples samples, double freq, std::string label="", Electrode::WeakPtr electrode=Electrode::WeakPtr());

    /**
     * @brief Adds sample at the end of the signal.
     * @param sample New sample.
     */
    void addSample(double sample);

    /**
     * @brief Getter.
     * @param time A moment in time.
     * @param normalize If true, the sample will be normalized.
     * @return The sample value at the specified moment.
     */
    double getSampleAtTime(double time, bool normalize = false) const;

    /**
     * @brief Getter.
     * @param time A moment in time.
     * @return The sample index at the specified moment.
     */
    unsigned int getIdxAtTime(double time) const;

    /**
     * @brief Normalizes the sample using signal minimum and maximum to a <-1; 1> range.
     * @param sample Sample to normalize.
     * @return Normalized sample.
     */
    double normalizeSample(double sample) const;

    /**
     * @brief Getter.
     * @return Number of samples in the signal.
     */
    unsigned int sampleCount() const;

    /**
     * @brief Getter.
     * @return Duration of the signal in seconds.
     */
    double duration() const;

    /**
     * @brief Getter.
     * @return Signal sampling frequency in Hertz.
     */
    double samplingFreq() const;

    /**
     * @brief Getter.
     * @return Signal samples.
     */
    const Samples &data() const;

    /**
     * @brief Setter.
     * @param samples New samples that will substitue current ones.
     */
    void data(Samples samples);

    /**
     * @brief Getter.
     * @return Label of the signal.
     */
    std::string label() const;

    /**
     * @brief Setter.
     * @param label New label for the signal.
     */
    void label(std::string label);

    /**
     * @brief Getter.
     * @return Electrode associated with the signal.
     */
    Electrode::WeakPtr electrode() const;

    /**
     * @brief Setter.
     * @param electrode Electrode to associate with the signal.
     */
    void electrode(Electrode::WeakPtr electrode);
    void clearElectrode();

    /**
     * @brief Getter.
     * @return Minimum possible value of the signal.
     */
    double minAmplitude() const;

    /**
     * @brief Setter.
     * @param amp Minimum possible value of the signal.
     */
    void minAmplitude(double amp);

    /**
     * @brief Getter.
     * @return Maximum possible value of the signal.
     */
    double maxAmplitude() const;

    /**
     * @brief Detter.
     * @param amp Maximum possible value of the signal.
     */
    void maxAmplitude(double amp);

private:
    SignalData();
    SignalData(Samples data);

    std::vector<double> _data;
    double _samplingFreq;

    double _minAmplitude;
    double _maxAmplitude;

    // Label as annotated in input file
    std::string _label;
    // Associated electrode
    Electrode::WeakPtr _electrode;
};

#endif
