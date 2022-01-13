#include "linear-fm-waveform.h"

namespace plasma {

Eigen::ArrayXcd LinearFMWaveform::sample() {
  // TODO: Document this
  // Sample interval
  double ts = 1 / samp_rate();
  double t;
  // Number of samples per pulse
  size_t num_samps_pulse = static_cast<int>(samp_rate() * pulse_width());
  Eigen::ArrayXcd out(num_samps_pulse);
  for (size_t i = 0; i < num_samps_pulse; i++) {
    t = i * ts;
    out[i] = std::exp(
        Im * (2 * M_PI) *
        (-bandwidth() / 2 * t + bandwidth() / (2 * pulse_width()) * pow(t, 2)));
  }

  return out;
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