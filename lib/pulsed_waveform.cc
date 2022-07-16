#include "pulsed_waveform.h"

#include <iostream>
#include <numeric>

namespace plasma {

PulsedWaveform::PulsedWaveform() : Waveform() {
  d_prf = 0;
  d_pulse_width = 0;
}

PulsedWaveform::PulsedWaveform(double pulse_width, double prf) {
  d_pulse_width = pulse_width;
  d_prf = prf;
  d_prf_schedule = {prf};
}

PulsedWaveform::PulsedWaveform(double pulse_width,
                               std::vector<double> prf_schedule) {
  d_pulse_width = pulse_width;
  d_prf_schedule = prf_schedule;
  d_prf = prf_schedule[0];
}

af::array PulsedWaveform::step() {
  double pri = 1 / d_prf;
  size_t num_samps_pri = round(d_samp_rate * pri);
  size_t num_samps_pulse = round(d_samp_rate * d_pulse_width);
  af::array wave = af::constant(0, num_samps_pri, c32);
  wave(af::seq(num_samps_pulse)) = sample();
  // Update the PRF for the next pulse
  d_prf_counter = (d_prf_counter + 1) % d_prf_schedule.size();
  d_prf = d_prf_schedule[d_prf_counter];
  return wave;
}

} // namespace plasma