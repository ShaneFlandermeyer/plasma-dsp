#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <complex>
#include <vector>

class Waveform {
  public:
    // Waveform sample rate
    double sampRate;
    // Return a vector containing the waveform samples
    virtual std::vector<std::complex<float>> sample() = 0;
};

#endif