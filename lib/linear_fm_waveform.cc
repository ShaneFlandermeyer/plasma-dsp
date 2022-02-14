#include "linear_fm_waveform.h"

namespace plasma {

Eigen::ArrayXcd LinearFMWaveform::sample(double t1, double t2) {
  // Handle default time index arguments
  if (t1 == -1) 
    t1 = 0; 
  if (t2 == -1) t2 = pulse_width();
  // Sample interval
  double ts = 1 / samp_rate();
  size_t num_samps = static_cast<int>(samp_rate() * (t2 - t1));
  Eigen::ArrayXd t =
      Eigen::ArrayXd::LinSpaced(num_samps, 0, num_samps-1) * ts + t1;
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