#include "square_waveform.h"

#include <algorithm>
#include <cmath>

namespace plasma {
  
af::array SquareWaveform::sample() {
  // Number of samples per pulse
  size_t num_samp_pulse = static_cast<size_t>(d_samp_rate * d_pulse_width);
  return af::constant(1,num_samp_pulse,c32);
}

SquareWaveform::SquareWaveform() : PulsedWaveform() {}

SquareWaveform::SquareWaveform(double pulse_width, double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::SquareWaveform(double pulse_width, af::array prf,
                               double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {}

SquareWaveform::~SquareWaveform() {}
}