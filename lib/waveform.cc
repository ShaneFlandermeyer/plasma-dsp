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

void Waveform::FrequencyShift(std::vector<std::complex<double>> &waveform,
                              double offset) {
  for (auto i = 0; i < waveform.size(); i++)
    waveform[i] *= exp(Im * 2.0 * M_PI * offset * (double)i / d_samp_rate);
}

std::vector<std::complex<double>> Waveform::waveform() {
  auto samples = sample();
  FrequencyShift(samples, d_freq_offset);
  return samples;
}

std::vector<std::complex<double>> Waveform::MatchedFilter() {
  auto mf = waveform();
  std::reverse(mf.begin(),mf.end());
  mf = conj(mf);
  return mf;

}

}  // namespace plasma