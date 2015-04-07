#include "signalWindow.h"


FilterWindow::FilterWindow(unsigned int halfLength) :
    _length(2 * halfLength + 1)
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
