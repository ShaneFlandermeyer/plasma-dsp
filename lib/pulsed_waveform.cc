#include "pulsed_waveform.h"

#include <iostream>
#include <numeric>

namespace plasma {

PulsedWaveform::PulsedWaveform() : Waveform() {
  d_prf = af::array();
  d_pulse_width = 0;
}

PulsedWaveform::PulsedWaveform(double pulse_width, double prf) {
  d_pulse_width = pulse_width;
  d_prf = af::constant(prf, 1, f64);
}

PulsedWaveform::PulsedWaveform(double pulse_width, af::array prf) {
  d_pulse_width = pulse_width;
  d_prf = prf;
}

af::array PulsedWaveform::step() {
  double pri = 1 / d_prf(d_prf_counter).scalar<double>();
  // af::array pri = 1 / d_prf;
  size_t num_samps_pri = round(d_samp_rate * pri);
  size_t num_samps_pulse = round(d_samp_rate * d_pulse_width);
  af::array wave = af::constant(0, num_samps_pri, c32);
  wave(af::seq(num_samps_pulse)) = sample();
  d_prf_counter = (d_prf_counter + 1) % d_prf.elements();
  return wave;
}

// TODO: This returns the whole pulse train
// af::array PulsedWaveform::step() {
//   // Determine the number of samples per PRI (including zeros), and if there
//   is
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
//   af::array wave = af::array::Zero(num_samps_total);
//   for (const size_t &index : start_index) {
//     af::array data = sample();
//     wave(Eigen::seqN(index, data.size())) = data;
//   }
//   return wave;
// }

} // namespace plasma