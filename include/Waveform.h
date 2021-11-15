#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <complex>
#include <vector>

class Waveform {
  virtual std::vector<std::complex<float>> sample() = 0;
};

#endif