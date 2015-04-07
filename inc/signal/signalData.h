#ifndef SIGNAL_DATA_H
#define SIGNAL_DATA_H

#include <memory>
#include <vector>
#include "safePtr.h"
#include "electrode.h"

class SignalData
{
public:
    typedef std::vector<double> Samples;
    typedef std::shared_ptr<SignalData> Ptr;
    typedef std::shared_ptr<const SignalData> PtrConst;
    typedef SafePtr<SignalData> WeakPtr;
    typedef SafePtr<const SignalData> WeakPtrConst;

    static Ptr create();
    //static Ptr create(unsigned int size);
    static Ptr create(Samples samples, double freq, std::string label="", Electrode::WeakPtr electrode=Electrode::WeakPtr());

    void addSample(double sample);
    double getSampleAtTime(double time, bool normalize = false) const;
    unsigned int getIdxAtTime(double time) const;
    double normalizeSample(double sample) const;

    unsigned int sampleCount() const;

    double duration() const;
    double samplingFreq() const;

    const Samples &data() const;
    void data(Samples samples);

    std::string label() const;
    void label(std::string label);

    Electrode::WeakPtr electrode() const;
    void electrode(Electrode::WeakPtr electrode);
    void clearElectrode();

    double minAmplitude() const;
    void minAmplitude(double amp);

    double maxAmplitude() const;
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
