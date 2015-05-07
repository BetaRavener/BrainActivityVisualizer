#include "hammingWindow.h"
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

HammingWindow::HammingWindow(unsigned int length, double alfa) :
    FilterWindow(length)
{
    double beta = 1.0 - alfa;
    double angularCoefficient = 2 * glm::pi<double>() / (_length - 1);
    double sum = 0.0;
    for (unsigned int i = 0; i < _length; i++)
    {
        _coefficients[i] = alfa - beta * glm::cos(angularCoefficient * i);

        sum += _coefficients[i];
    }

    // Normalize the coefficients to maintain the average of signal
    for (unsigned int i = 0; i < _length; i++)
    {
        _coefficients[i] *= (_length / sum);
    }
}

HammingWindow::~HammingWindow()
{

}

