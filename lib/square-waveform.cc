#include "square-waveform.h"

#include <algorithm>
#include <cmath>

namespace plasma {
Eigen::ArrayXcd SquareWaveform::sample() {
  // Number of samples per pulse
  int num_samps_pulse = static_cast<int>(pulse_width() * samp_rate());
  return Eigen::ArrayXcd::Ones(num_samps_pulse);
}

SquareWaveform::SquareWaveform() : PulsedWaveform() {}

SquareWaveform::SquareWaveform(double pulse_width, double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::SquareWaveform(double pulse_width, std::vector<double> prf,
                               double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::~SquareWaveform() {}
}