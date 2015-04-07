#include "blackmanWindow.h"
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

BlackmanWindow::BlackmanWindow(unsigned int halfLength, double alfa) :
    FilterWindow(halfLength)
{
    double a0 = (1.0 - alfa) * 0.5;
    double a1 = 0.5;
    double a2 = alfa * 0.5;
    double angularCoefficient = 2 * glm::pi<double>() / (_length - 1);
    for (unsigned int i = 0; i < _length; i++)
    {
        _coefficients[i] = a0 -
                           a1 * glm::cos(angularCoefficient * i) +
                           a2 * glm::cos(2.0 * angularCoefficient * i);
    }
}

BlackmanWindow::~BlackmanWindow()
{

}

