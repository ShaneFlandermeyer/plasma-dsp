#include "plasma-dsp/squarewaveform.h"

#include <algorithm>
#include <cmath>

std::vector<std::complex<double>> SquareWaveform::pulse() {
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(pulsewidth() * sampRate());
  // Output vector
  std::vector<std::complex<double>> wave(nSampsPulse);
  std::fill(wave.begin(), wave.end(), std::complex<double>(1, 0));
  return wave;
}

SquareWaveform::SquareWaveform() : PulsedWaveform() {}

SquareWaveform::SquareWaveform(double pulsewidth, double prf, double sampRate)
    : Waveform(sampRate), PulsedWaveform(pulsewidth, prf) {}

SquareWaveform::SquareWaveform(double pulsewidth, std::vector<double> prf,
                               double sampRate)
    : Waveform(sampRate), PulsedWaveform(pulsewidth, prf) {}

SquareWaveform::~SquareWaveform() {}