#include "squarewaveform.h"

#include <cmath>
#include <algorithm>

/*
 * Return a complete PRF of a square wave
 */
std::vector<std::complex<double>> SquareWaveform::sample() {
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(pulsewidth() * sampRate());
  // Output vector
  std::vector<std::complex<double>> wave(nSampsPulse);
  std::fill(wave.begin(), wave.end(), std::complex<double>(1, 0));
  return wave;
}

/*
 * Default constructor
 */
SquareWaveform::SquareWaveform() {
  pulsewidth(0);
  prf(0);
  sampRate(0);
}

/*
 * Non-trivial constructor
 */
SquareWaveform::SquareWaveform(double pulsewidth, double prf, double sampRate) {
  this->pulsewidth(pulsewidth);
  this->prf(prf);
  this->sampRate(sampRate);
}

SquareWaveform::SquareWaveform(double pulsewidth, std::vector<double> prf, double sampRate) {
  this->pulsewidth(pulsewidth);
  this->prf(prf);
  this->sampRate(sampRate);
}

/*
 * Destructor
 */
SquareWaveform::~SquareWaveform() {}