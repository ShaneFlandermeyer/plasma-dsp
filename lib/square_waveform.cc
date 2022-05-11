#include "square_waveform.h"

#include <algorithm>
#include <cmath>

namespace plasma {
  
Eigen::ArrayXcd SquareWaveform::sample() {
  // Number of samples per pulse
  size_t num_samps_pulse = static_cast<size_t>(d_samp_rate * d_pulse_width);
  return Eigen::ArrayXcd::Ones(num_samps_pulse);
}

SquareWaveform::SquareWaveform() : PulsedWaveform() {}

SquareWaveform::SquareWaveform(double pulse_width, double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::SquareWaveform(double pulse_width, Eigen::ArrayXd prf,
                               double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::~SquareWaveform() {}
}