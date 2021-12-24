#include "squarewaveform.h"

#include <algorithm>
#include <cmath>

namespace plasma {
std::vector<std::complex<double>> SquareWaveform::sample() {
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(pulsewidth() * samp_rate());
  // Output vector
  std::vector<std::complex<double>> wave(nSampsPulse);
  std::fill(wave.begin(), wave.end(), std::complex<double>(1, 0));
  return wave;
}

SquareWaveform::SquareWaveform() : PulsedWaveform() {}

SquareWaveform::SquareWaveform(double pulsewidth, double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulsewidth, prf) {}

SquareWaveform::SquareWaveform(double pulsewidth, std::vector<double> prf,
                               double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulsewidth, prf) {}

SquareWaveform::~SquareWaveform() {}
}