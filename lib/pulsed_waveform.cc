#include "pulsed_waveform.h"

#include <iostream>
#include <numeric>

namespace plasma {

PulsedWaveform::PulsedWaveform() : Waveform() {
  d_prf = Eigen::ArrayXd();
  d_pulse_width = 0;
}

PulsedWaveform::PulsedWaveform(double pulse_width, double prf) {
  d_pulse_width = pulse_width;
  d_prf = Eigen::ArrayXd(1);
  d_prf << prf;
}

PulsedWaveform::PulsedWaveform(double pulse_width, Eigen::ArrayXd prf) {
  d_pulse_width = pulse_width;
  d_prf = prf;
}

Eigen::ArrayXcd PulsedWaveform::step() {
  double pri = 1 / d_prf(d_prf_counter);
  size_t num_samps_pri = round(d_samp_rate * pri);
  size_t num_samps_pulse = round(d_samp_rate * d_pulse_width);
  Eigen::ArrayXcd wave = Eigen::ArrayXcd::Zero(num_samps_pri);
  wave.head(num_samps_pulse) = sample();
  d_prf_counter = (d_prf_counter + 1) % d_prf.size();
  return wave;
}

// TODO: This returns the whole pulse train
// Eigen::ArrayXcd PulsedWaveform::step() {
//   // Determine the number of samples per PRI (including zeros), and if there is
//   // more than one PRF we also need to determine the starting index of the
//   // nonzero part for each pulse
//   Eigen::ArrayXd pri = 1 / d_prf;
//   Eigen::Array<size_t, Eigen::Dynamic, 1> num_samps_pri =
//       round(pri * samp_rate()).cast<size_t>();
//   Eigen::Array<size_t, Eigen::Dynamic, 1> start_index =
//       Eigen::Array<size_t, Eigen::Dynamic, 1>::Zero(pri.size());
//   if (pri.size() > 1)
//     std::partial_sum(num_samps_pri.begin(), num_samps_pri.end(),
//                      start_index.data());

//   // Create the full pulse train by filling all the nonzero indices with the
//   // appropriate values
//   double duration = pri.sum();
//   size_t num_samps_total = round(duration * samp_rate());
//   Eigen::ArrayXcd wave = Eigen::ArrayXcd::Zero(num_samps_total);
//   for (const size_t &index : start_index) {
//     Eigen::ArrayXcd data = sample();
//     wave(Eigen::seqN(index, data.size())) = data;
//   }
//   return wave;
// }

} // namespace plasma