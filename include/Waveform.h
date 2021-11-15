#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <complex>
#include <vector>
#include "constants.h"

class Waveform {
  public:
    // Waveform sample rate
    double sampRate;
    // Return a vector containing the waveform samples
    virtual std::vector<std::complex<double>> sample() = 0;
};

#endif