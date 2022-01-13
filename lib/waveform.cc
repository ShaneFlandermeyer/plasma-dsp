#include "waveform.h"

namespace plasma {

Waveform::Waveform() {
  d_samp_rate = 0;
  d_freq_offset = 0;
}

Waveform::Waveform(double samp_rate) {
  d_samp_rate = samp_rate;
  d_freq_offset = 0;
}

void Waveform::FrequencyShift(Eigen::ArrayXcd &waveform, double offset) {
  std::complex<double> freq = Im * 2.0 * M_PI * offset / d_samp_rate;
  for (auto i = 0; i < waveform.size(); i++)
    waveform[i] *= exp(freq * (double)i);
}

Eigen::ArrayXcd Waveform::waveform() {
  Eigen::ArrayXcd samples = sample();
  FrequencyShift(samples, d_freq_offset);
  return samples;
}

Eigen::ArrayXcd Waveform::MatchedFilter() { return conj(waveform().reverse()); }

} // namespace plasma