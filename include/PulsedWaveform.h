#ifndef PULSED_WAVEFORM_H
#define PULSED_WAVEFORM_H
#include "Waveform.h"
class PulsedWaveform : public Waveform {
 protected:
  // Pulse repetition frequency (Hz)
  std::vector<double> d_prf;
  // Pulse width (s)
  double d_pulsewidth;

 public:
  // Getters 
  auto prf() const { return d_prf; }
  auto pulsewidth() const { return d_pulsewidth; }
  // Setters
  auto prf(double prf) { d_prf.push_back(prf); }
  auto prf(std::vector<double> prf) { d_prf = prf; }
  auto pulsewidth(double pulsewidth) { d_pulsewidth = pulsewidth; }
  // TODO: Rename this to something not dumb
  std::vector<std::complex<double>> getWaveform();
};
#endif