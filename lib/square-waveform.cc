#include "square-waveform.h"

#include <algorithm>
#include <cmath>

namespace plasma {
std::vector<std::complex<double>> SquareWaveform::sample() {
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(pulse_width() * samp_rate());
  // Output vector
  std::vector<std::complex<double>> wave(nSampsPulse);
  std::fill(wave.begin(), wave.end(), std::complex<double>(1, 0));
  return wave;
}

SquareWaveform::SquareWaveform() : PulsedWaveform() {}

SquareWaveform::SquareWaveform(double pulse_width, double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::SquareWaveform(double pulse_width, std::vector<double> prf,
                               double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::~SquareWaveform() {}
}