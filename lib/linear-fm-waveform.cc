#include "linear-fm-waveform.h"

namespace plasma {

Eigen::ArrayXcd LinearFMWaveform::sample() {
  // TODO: Document this
  // Sample interval
  double ts = 1 / samp_rate();
  // Number of samples per pulse
  size_t num_samps_pulse = static_cast<int>(samp_rate() * pulse_width());
  // Compute sample times
  Eigen::ArrayXd t(num_samps_pulse, ts);
  t(0) = 0;
  std::accumulate(t.begin(), t.end(), t.begin());

  return exp(
      Im * (2 * M_PI) *
      (-bandwidth() / 2 * t + bandwidth() / (2 * pulse_width()) * t.square()));
  // double t;
  // std::vector<std::complex<double>> wave(num_samps_pulse, 0);
  // for (int n = 0; n < num_samps_pulse; n++) {
  //   t = n * ts;
  //   double phase = -bandwidth() / 2 * t +
  //                  bandwidth() / (2 * pulse_width()) * std::pow(t, 2);
  //   wave[n] = std::exp(Im * (2 * M_PI) * phase);
  // }
  // return wave;
}

LinearFMWaveform::LinearFMWaveform() : PulsedWaveform() { d_bandwidth = 0; }

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {
  d_bandwidth = bandwidth;
}

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   std::vector<double> prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {
  d_bandwidth = bandwidth;
}

} // namespace plasma