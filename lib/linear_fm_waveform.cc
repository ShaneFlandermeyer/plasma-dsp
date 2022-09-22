#include "linear_fm_waveform.h"
#include <iostream>
namespace plasma {

af::array LinearFMWaveform::sample() {
  // Sample interval
  double ts = 1 / d_samp_rate;
  size_t num_samp = round(d_samp_rate * d_pulse_width);
  af::array t = af::range(af::dim4(num_samp), -1, f64) * ts;
  af::array phase =
      af::Im * M_PI *
      (-bandwidth() * t + bandwidth() / pulse_width() * af::pow(t, 2));
  return af::exp(phase);
}

LinearFMWaveform::LinearFMWaveform() : PulsedWaveform() { d_bandwidth = 0; }

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   double samp_rate, double prf)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {
  d_bandwidth = bandwidth;
}

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   double samp_rate, std::vector<double> prf)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf) {
  d_bandwidth = bandwidth;
}

} // namespace plasma