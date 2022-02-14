#include "square_waveform.h"

#include <algorithm>
#include <cmath>

namespace plasma {
Eigen::ArrayXcd SquareWaveform::sample(double t1, double t2) {
  // Number of samples per pulse
  if (t1 == -1) t1 = 0;
  if (t2 == -1) t2 = pulse_width();
  int num_samps_pulse = static_cast<int>((t2-t1) * samp_rate());
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