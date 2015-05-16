// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef FILTER_WINDOW_H
#define FILTER_WINDOW_H

#include <deque>
#include <vector>

/**
 * @brief The FilterWindow class is a base class for filtering windows.
 */
class FilterWindow
{
public:
    /**
     * @brief FilterWindow
     * @param length The length of thw window in samples.
     */
    FilterWindow(unsigned int length);
    virtual ~FilterWindow();

    /**
     * @brief Getter.
     * @return Length of the window.
     */
    unsigned int length();

    /**
     * @brief Getter.
     * @return Length of the window divided by 2.
     */
    unsigned int halfLength();

    /**
     * @brief Applies window to a vector of values. The vector and window lengths must be the same.
     * @param vec
     */
    void applyTo(std::vector<float> &vec);

    /**
     * @brief Applies window to a vector of values. The vector and window lengths must be the same.
     * @param vec
     */
    void applyTo(std::vector<double> &vec);

    /**
     * @brief Adds sample to the window. If the window is full, the oldest sample is removed.
     * @param sample New sample.
     */
    void addSample(double sample);

    /**
     * @brief Clears the window.
     */
    void clear();

    /**
     * @brief Returns sample at the index with window coefficient applied.
     * @param idx Index of the sample.
     * @return Weighted sample.
     */
    double operator [](unsigned int idx) const;

    /**
     * @brief Getter.
     * @return True if the window is full.
     */
    bool isFilled() const;

protected:
    unsigned int _length;
    double* _coefficients;
private:
    std::deque<double> _data;
};

#endif
