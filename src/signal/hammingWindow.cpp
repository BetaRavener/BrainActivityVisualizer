#include "hammingWindow.h"
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

HammingWindow::HammingWindow(unsigned int halfLength, double alfa) :
    FilterWindow(halfLength)
{
    double beta = 1.0 - alfa;
    double angularCoefficient = 2 * glm::pi<double>() / (_length - 1);
    for (unsigned int i = 0; i < _length; i++)
    {
        _coefficients[i] = alfa - beta * glm::cos(angularCoefficient * i);
    }
}

HammingWindow::~HammingWindow()
{

}

