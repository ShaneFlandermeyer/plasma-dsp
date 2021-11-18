#include "LinearFMWaveform.h"

/*
 * Generate a PRI of data for the given waveform
 */
std::vector<std::complex<double>> LinearFMWaveform::sample() {
  // Sample interval
  double ts = 1 / sampRate();
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(sampRate() * pulsewidth());
  // TODO: Handle multiple PRF values
  int nSampsPri = static_cast<int>(sampRate() / prf()[0]);
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
  this->bandwidth(bandwidth);
  this->pulsewidth(pulsewidth);
  this->prf(prf);
  this->sampRate(sampRate);
}

LinearFMWaveform::LinearFMWaveform(){
  bandwidth(0);
  pulsewidth(0);
  sampRate(0);
  prf(0);
}

LinearFMWaveform::~LinearFMWaveform() {}