#include "SquareWaveform.h"

#include <cmath>

/*
 * Return a complete PRF of a square wave
 */
std::vector<std::complex<double>> SquareWaveform::sample() {
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(pulsewidth() * sampRate());
  // Number of samples per PRF
  int nSampsPri = static_cast<int>(sampRate() / prf());
  // Output vector
  std::vector<std::complex<double>> out(nSampsPri);
  // TODO: Get the normalization right here
  double mag = 1;
  for (size_t i = 0; i < nSampsPulse; i++) {
    out[i] = std::complex<double>(mag,0);
  }
  return out;
}

/*
 * Non-trivial constructor
 */
SquareWaveform::SquareWaveform(double pulsewidth, double prf, double sampRate) {
  d_pulsewidth = pulsewidth;
  d_prf = prf;
  d_sampRate = sampRate;
}

/*
 * Destructor
 */
SquareWaveform::~SquareWaveform() {}