#include "pulsed-waveform.h"

#include <iostream>
#include <numeric>

namespace plasma {
PulsedWaveform::PulsedWaveform() : Waveform() {
  d_prf = Eigen::ArrayXd();
  d_pulse_width = 0;
}

PulsedWaveform::PulsedWaveform(double pulse_width, double prf) {
  d_pulse_width = pulse_width;
  d_prf = {prf};
}

PulsedWaveform::PulsedWaveform(double pulse_width, Eigen::ArrayXd prf) {
  d_pulse_width = pulse_width;
  d_prf = prf;
}

Eigen::ArrayXcd PulsedWaveform::pulse() {
  Eigen::ArrayXd pri = 1 / d_prf;
  Eigen::Array<size_t, Eigen::Dynamic, 1> num_samps_pri =
      round(pri * samp_rate()).cast<size_t>();
  Eigen::Array<size_t, Eigen::Dynamic, 1> start_index(num_samps_pri.size());
  std::partial_sum(num_samps_pri.begin(),num_samps_pri.end(),start_index.begin());
  double duration = pri.sum();
  size_t num_samps_total = static_cast<size_t>(duration * samp_rate());
  Eigen::ArrayXcd wave(num_samps_total);
  for (const size_t& index : start_index) {
    Eigen::ArrayXcd data = waveform();
    wave(Eigen::seqN(index,data.size())) = data;
  }
  return wave;
}
} // namespace plasma