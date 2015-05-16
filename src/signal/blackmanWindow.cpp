// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "blackmanWindow.h"
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

BlackmanWindow::BlackmanWindow(unsigned int length, double alfa) :
    FilterWindow(length)
{
    double a0 = (1.0 - alfa) * 0.5;
    double a1 = 0.5;
    double a2 = alfa * 0.5;
    double angularCoefficient = 2 * glm::pi<double>() / (_length - 1);
    double sum = 0.0;
    for (unsigned int i = 0; i < _length; i++)
    {
        _coefficients[i] = a0 -
                           a1 * glm::cos(angularCoefficient * i) +
                           a2 * glm::cos(2.0 * angularCoefficient * i);

        sum += _coefficients[i];
    }

    // Normalize the coefficients to maintain the average of signal
    for (unsigned int i = 0; i < _length; i++)
    {
        _coefficients[i] *= (_length / sum);
    }
}

BlackmanWindow::~BlackmanWindow()
{

}

