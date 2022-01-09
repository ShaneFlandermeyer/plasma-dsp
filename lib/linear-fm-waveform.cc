#include "linear-fm-waveform.h"

namespace plasma {

std::vector<std::complex<double>> LinearFMWaveform::sample() {
  // Sample interval
  double ts = 1 / samp_rate();
  // Number of samples per pulse
  int num_samps_pulse = static_cast<int>(samp_rate() * pulse_width());
  double t;
  std::vector<std::complex<double>> wave(num_samps_pulse, 0);
  for (int n = 0; n < num_samps_pulse; n++) {
    t = n * ts;
    double phase = -bandwidth() / 2 * t +
                   bandwidth() / (2 * pulse_width()) * std::pow(t, 2);
    wave[n] = std::exp(Im * (2 * M_PI) * phase);
  }
  return wave;
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

}  // namespace plasma