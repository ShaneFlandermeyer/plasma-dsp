#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <complex>
#include <vector>

#include "constants.h"

class Waveform {
 public:
  // Return a vector containing the waveform samples
  virtual std::vector<std::complex<double>> sample() = 0;
  double sampRate() const { return d_sampRate; }

 protected:
  // Waveform sample rate
  double d_sampRate;
};

#endif