#include "waveform.h"

namespace plasma {

std::vector<std::complex<double>>
Waveform::waveform() {
  auto samples = sample();
  // Apply frequency shift to each sample of the waveform
  for (auto i = 0; i < samples.size(); i++) {
    samples[i] *= exp(Im*2.0*M_PI*d_freqOffset*(double)i/d_sampRate);
  }
  return samples;

}

Waveform::Waveform() {
  d_sampRate = 0;
  d_freqOffset = 0;
}

Waveform::Waveform(double sampRate) { d_sampRate = sampRate; }
}  // namespace plasma