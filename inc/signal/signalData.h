#ifndef SIGNAL_DATA_H
#define SIGNAL_DATA_H

#include <memory>
#include <vector>

class SignalData
{
public:
    typedef std::shared_ptr<SignalData> Ptr;
    typedef std::shared_ptr<const SignalData> PtrConst;

    static Ptr create();
    static Ptr create(unsigned int size);

    void addSample(double sample);

    unsigned int sampleCount() const;

    double duration() const;
    double samplingFreq() const;

    const std::vector<double> &data() const;
    double *writeAccess();

private:
    SignalData();

    std::vector<double> _data;
    double _samplingFreq;
};

#endif
