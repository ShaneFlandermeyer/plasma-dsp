#ifndef PULSED_WAVEFORM_H
#define PULSED_WAVEFORM_H
#include "Waveform.h"
class PulsedWaveform : public Waveform {
 protected:
  // Pulse repetition frequency (Hz)
  double d_prf;
  // Pulse width (s)
  double d_pulsewidth;

 public:
  // Getters and setters
  auto prf() const { return d_prf; }
  auto prf(double prf) { d_prf = prf; }
  auto pulsewidth() const { return d_pulsewidth; }
  auto pulsewidth(double pulsewidth) { d_pulsewidth = pulsewidth; }
};
#endif