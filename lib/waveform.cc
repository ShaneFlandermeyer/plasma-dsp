#include "waveform.h"

namespace plasma {

void Waveform::FrequencyShift(std::vector<std::complex<double>> &waveform,
                              double offset) {
  for (auto i = 0; i < waveform.size(); i++) {
    waveform[i] *= exp(Im * 2.0 * M_PI * offset * (double)i / d_samp_rate);
  }

}  // namespace plasma

std::vector<std::complex<double>> Waveform::waveform() {
  auto samples = sample();
  FrequencyShift(samples, d_freq_offset);
  return samples;
}

Waveform::Waveform() {
  d_samp_rate = 0;
  d_freq_offset = 0;
}

Waveform::Waveform(double samp_rate) { d_samp_rate = samp_rate; }
}  // namespace plasma