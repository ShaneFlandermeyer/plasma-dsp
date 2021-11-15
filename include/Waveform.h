#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <complex>
#include <vector>

#include "constants.h"

class Waveform {
 protected:
  // Waveform sample rate
  double d_sampRate;

 public:
  // Return a vector containing the waveform samples for one PRI
  virtual std::vector<std::complex<double>> sample() = 0;
  // Getters and setters
  auto sampRate() const { return d_sampRate; }
  auto sampRate(double sampRate) { d_sampRate = sampRate; }
};

#endif