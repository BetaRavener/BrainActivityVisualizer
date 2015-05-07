#ifndef FILTER_WINDOW_H
#define FILTER_WINDOW_H

#include <deque>
#include <vector>

class FilterWindow
{
public:
    FilterWindow(unsigned int length);
    virtual ~FilterWindow();
    unsigned int length();
    unsigned int halfLength();

    void applyTo(std::vector<float> &vec);
    void applyTo(std::vector<double> &vec);
    void addSample(double sample);
    void clear();

    double operator [](unsigned int idx) const;

    bool isFilled() const;

protected:
    unsigned int _length;
    double* _coefficients;
private:
    std::deque<double> _data;
};

#endif
