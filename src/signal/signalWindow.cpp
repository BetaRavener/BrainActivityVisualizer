#include "signalWindow.h"
#include <stdexcept>

FilterWindow::FilterWindow(unsigned int length) :
    _length(length)
{
    _coefficients = new double[_length];

    for (unsigned int i = 0; i < _length; i++)
        _coefficients[i] = 1.0;
}

FilterWindow::~FilterWindow()
{
    delete[] _coefficients;
    _coefficients = nullptr;
}

unsigned int FilterWindow::length()
{
    return _length;
}

unsigned int FilterWindow::halfLength()
{
    return _length / 2;
}

void FilterWindow::applyTo(std::vector<float> &vec)
{
    if (vec.size() != _length)
        throw new std::range_error("Length of vector must be equal to length of the window.");

    for (unsigned int i = 0; i < vec.size(); i++)
        vec[i] *= _coefficients[i];
}

void FilterWindow::applyTo(std::vector<double>& vec)
{
    if (vec.size() != _length)
        throw new std::range_error("Length of vector must be equal to length of the window.");

    for (unsigned int i = 0; i < vec.size(); i++)
        vec[i] *= _coefficients[i];
}

void FilterWindow::addSample(double sample)
{
    _data.push_back(sample);
    if (_data.size() > _length)
        _data.pop_front();
}

void FilterWindow::clear()
{
    _data.clear();
}

double FilterWindow::operator [](unsigned int idx) const
{
    if (isFilled())
    {
        return _coefficients[idx] * _data[idx];
    }
    else
        return 0.0;
}

bool FilterWindow::isFilled() const
{
    return _data.size() == _length;
}
