#include "waveform.h"

namespace plasma {

std::vector<std::complex<double>>
Waveform::waveform() {
  auto samples = sample();
  // Apply frequency shift to each sample of the waveform
  for (auto i = 0; i < samples.size(); i++) {
    samples[i] *= exp(Im*2.0*M_PI*d_freq_offset*(double)i/d_samp_rate);
  }
  return samples;

}

Waveform::Waveform() {
  d_samp_rate = 0;
  d_freq_offset = 0;
}

Waveform::Waveform(double samp_rate) { d_samp_rate = samp_rate; }
}  // namespace plasma