// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

#include "signalData.h"
#include "lowpassFilter.h"
#include "highpassFilter.h"
#include "signalWindow.h"
#include "hammingWindow.h"
#include "blackmanWindow.h"

// The signal is considered to be 250 Hz
#define TEST_SAMPLING_FREQ 250.0

void testLow(SignalData::Ptr sig, unsigned int order, double cutoff, FilterWindow win)
{
    LowpassFilter f(order, cutoff, sig->samplingFreq());
    f.process(sig, win);
}

void testHigh(SignalData::Ptr sig, unsigned int order, double cutoff, FilterWindow win)
{
    HighpassFilter f(order, cutoff, sig->samplingFreq());
    f.process(sig, win);
}

std::vector<double> testLowHamm(SignalData::Samples& data, unsigned int order, double cutoff)
{
    SignalData::Ptr sig = SignalData::create(data, TEST_SAMPLING_FREQ);
    testLow(sig, order, cutoff, HammingWindow(order*2+1));
    return sig->data();
}

std::vector<double> testHighHamm(SignalData::Samples& data, unsigned int order, double cutoff)
{
    SignalData::Ptr sig = SignalData::create(data, TEST_SAMPLING_FREQ);
    testHigh(sig, order, cutoff, HammingWindow(order*2+1));
    return sig->data();
}

std::vector<double> testLowBlack(SignalData::Samples& data, unsigned int order, double cutoff)
{
    SignalData::Ptr sig = SignalData::create(data, TEST_SAMPLING_FREQ);
    testLow(sig, order, cutoff, BlackmanWindow(order*2+1));
    return sig->data();
}

std::vector<double> testHighBlack(SignalData::Samples& data, unsigned int order, double cutoff)
{
    SignalData::Ptr sig = SignalData::create(data, TEST_SAMPLING_FREQ);
    testHigh(sig, order, cutoff, BlackmanWindow(order*2+1));
    return sig->data();
}

void saveTest(std::string filename, std::vector<double> data)
{
    std::ofstream fout(filename);
    for (double sample : data)
    {
        fout << sample << "\n";
    }
    fout.flush();
    fout.close();
}

int main(int argc, char *argv[])
{
    std::ifstream fin;
    fin.open("sig.txt");

    if (!fin)
        return -1;

    std::vector<double> sig;
    try
    {
        double d;
        while (fin >> d)
        {
            sig.push_back(d);
        }
    }
    catch (std::exception e)
    {
        return -1;
    }
    fin.close();

    // Lowpass
    // Hamming windows order 5
    saveTest("low5Hamm5", testLowHamm(sig, 5, 5));
    saveTest("low10Hamm5", testLowHamm(sig, 5, 10));
    // Hamming windows order 10
    saveTest("low5Hamm10", testLowHamm(sig, 10, 5));
    saveTest("low10Hamm10", testLowHamm(sig, 10, 10));
    // Blackman windows order 5
    saveTest("low5Black5", testLowBlack(sig, 5, 5));
    saveTest("low10Black5", testLowBlack(sig, 5, 10));
    // Blackman windows order 10
    saveTest("low5Black10", testLowBlack(sig, 10, 5));
    saveTest("low10Black10", testLowBlack(sig, 10, 10));

    // Highpass
    // Hamming windows order 5
    saveTest("high50Hamm5", testHighHamm(sig, 5, 50));
    saveTest("high100Hamm5", testHighHamm(sig, 5, 100));
    // Hamming windows order 10
    saveTest("high50Hamm10", testHighHamm(sig, 10, 50));
    saveTest("high100Hamm10", testHighHamm(sig, 10, 100));
    // Blackman windows order 5
    saveTest("high50Black5", testHighBlack(sig, 5, 50));
    saveTest("high100Black5", testHighBlack(sig, 5, 100));
    // Blackman windows order 10
    saveTest("high50Black10", testHighBlack(sig, 10, 50));
    saveTest("high100Black10", testHighBlack(sig, 10, 100));

    return 0;
}
