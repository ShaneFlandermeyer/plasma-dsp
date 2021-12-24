#include "linearfmwaveform.h"

namespace plasma {

std::vector<std::complex<double>> LinearFMWaveform::sample() {
  // Sample interval
  double ts = 1 / samp_rate();
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(samp_rate() * pulsewidth());
  double t;
  std::vector<std::complex<double>> wave(nSampsPulse, 0);
  for (int n = 0; n < nSampsPulse; n++) {
    t = n * ts;
    double phase = -bandwidth() / 2 * t +
                   bandwidth() / (2 * pulsewidth()) * std::pow(t, 2);
    wave[n] = std::exp(Im * (2 * M_PI) * phase);
  }
  return wave;
}

LinearFMWaveform::LinearFMWaveform() : PulsedWaveform() { d_bandwidth = 0; }

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulsewidth,
                                   double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulsewidth, prf) {
  d_bandwidth = bandwidth;
}

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulsewidth,
                                   std::vector<double> prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(pulsewidth, prf) {
  d_bandwidth = bandwidth;
}

}  // namespace plasma