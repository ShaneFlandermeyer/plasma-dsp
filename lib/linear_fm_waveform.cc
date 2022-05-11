#include "linear_fm_waveform.h"

namespace plasma {

Eigen::ArrayXcd LinearFMWaveform::sample() {
  // Sample interval
  double ts = 1 / d_samp_rate;
  size_t num_samps = round(d_samp_rate * d_pulse_width);
  Eigen::ArrayXd t =
      Eigen::ArrayXd::LinSpaced(num_samps, 0, num_samps - 1) * ts;
  Eigen::ArrayXcd out = exp(
      Im * (2 * M_PI) *
      (-bandwidth() / 2 * t + bandwidth() / (2 * pulse_width()) * pow(t, 2)));

  return out;
}

LinearFMWaveform::LinearFMWaveform() : PulsedWaveform() { d_bandwidth = 0; }

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {
  d_bandwidth = bandwidth;
}

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   Eigen::ArrayXd prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {
  d_bandwidth = bandwidth;
}

} // namespace plasma