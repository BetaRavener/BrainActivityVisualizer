// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <memory>
#include <vector>

/**
 * @brief The Spectrum class represents a frequency domain spectrum.
 */
class Spectrum
{
public:
    typedef std::shared_ptr<Spectrum> Ptr;
    typedef std::shared_ptr<const Spectrum> PtrConst;

    /**
     * @brief Creates a new spectrum.
     * @param data The values of the spectrum.
     * @param resolution Resolution of the spectrum in Hertz.
     * @param amplitude Amplitude of the spectrum. Should be equal to amplitude of the
     * signal from which it is being created.
     * @return The new spectrum.
     */
    static Ptr create(std::vector<double> data, double resolution, double amplitude);

    /**
     * @brief Getter.
     * @return Max frequency component contained in the spectrum.
     */
    double maxFrequency();

    /**
     * @brief Getter.
     * @return Resolution of the spectrum in Hertz.
     */
    double resolution();

    /**
     * @brief Getter.
     * @return Amplitude of the spectrum.
     */
    double amplitude();

    /**
     * @brief Normalizes a value of spectrum.
     * @param x The spectrum value.
     * @return Normalized spectrum value.
     */
    double normalize(double x);

    /**
     * @brief getIdxAtFreq
     * @param freq
     * @return
     */
    unsigned int getIdxAtFreq(double freq);

    /**
     * @brief Gets the mean value from the spectrum values in specified frequency range.
     * @param beginFreq The beginning of the frequency range.
     * @param endFreq The end of the frequency range.
     * @return Mean value.
     */
    double mean(double beginFreq, double endFreq);

    /**
     * @brief Gets the maximum value from the spectrum values in specified frequency range.
     * @param beginFreq The beginning of the frequency range.
     * @param endFreq The end of the frequency range.
     * @return Maximum value.
     */
    double max(double beginFreq, double endFreq);
private:
    Spectrum();

    std::vector<double> _data;
    double _resolution;
    double _amplitude;
};

#endif
