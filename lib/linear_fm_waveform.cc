#include "linear_fm_waveform.h"
#include <iostream>
namespace plasma {

af::array LinearFMWaveform::sample() {
  // Sample interval
  double ts = 1 / d_samp_rate;
  size_t num_samp = round(d_samp_rate * d_pulse_width);
  af::array t = af::range(af::dim4(num_samp), -1, f64) * ts;
  af::array phase =
      af::Im * 2 * M_PI *
      (d_start_freq * t + bandwidth() / (2*pulse_width()) * af::pow(t, 2));
  return af::exp(phase);
}

LinearFMWaveform::LinearFMWaveform() : PulsedWaveform() { d_bandwidth = 0; }

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   double samp_rate, double prf,
                                   double start_freq)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf),
      d_bandwidth(bandwidth), d_start_freq(start_freq) {}

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulse_width,
                                   double samp_rate, std::vector<double> prf,
                                   double sweep_offset)
    : Waveform(samp_rate), PulsedWaveform(pulse_width, prf),
      d_bandwidth(bandwidth), d_start_freq(sweep_offset) {}

} // namespace plasma