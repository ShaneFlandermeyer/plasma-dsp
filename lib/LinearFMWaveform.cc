#include "LinearFMWaveform.h"

LinearFMWaveform::LinearFMWaveform() {
  bandwidth = 0;
  pulsewidth = 0;
  sampRate = 0;
  prf = 0;
}
LinearFMWaveform::~LinearFMWaveform() {}

std::vector<std::complex<float>> LinearFMWaveform::sample() {
  // Imaginary number J
  std::complex<float> Im(0, 1);
  // Sample interval
  float ts = 1 / sampRate;
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(sampRate * pulsewidth);
  int nSampsPri = static_cast<int>(sampRate / prf);
  float t;
  std::vector<std::complex<float>> wave(nSampsPri, 0);
  for (int n = 0; n < nSampsPulse; n++) {
    t = n * ts;
    float phase =
        -bandwidth / 2 * t + bandwidth / (2 * pulsewidth) * std::pow(t, 2);
    wave[n] = std::exp(Im * (float)(2 * M_PI) * phase);
  }
  return wave;
}