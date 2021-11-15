#include "LinearFMWaveform.h"

/*
 * Generate a PRI of data for the given waveform
 */
std::vector<std::complex<double>> LinearFMWaveform::sample() {
  // Sample interval
  double ts = 1 / sampRate();
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(sampRate() * pulsewidth());
  int nSampsPri = static_cast<int>(sampRate() / prf());
  double t;
  std::vector<std::complex<double>> wave(nSampsPri, 0);
  for (int n = 0; n < nSampsPulse; n++) {
    t = n * ts;
    double phase =
        -bandwidth() / 2 * t + bandwidth() / (2 * pulsewidth()) * std::pow(t, 2);
    wave[n] = std::exp(Im * (double)(2 * M_PI) * phase);
  }
  return wave;
}

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulsewidth,
                                   double prf, double sampRate) {
  d_bandwidth = bandwidth;
  d_pulsewidth = pulsewidth;
  d_prf = prf;
  d_sampRate = sampRate;
}

LinearFMWaveform::LinearFMWaveform(){
  d_bandwidth = 0;
  d_pulsewidth = 0;
  d_sampRate = 0;
  d_prf = 0;
}

LinearFMWaveform::~LinearFMWaveform() {}