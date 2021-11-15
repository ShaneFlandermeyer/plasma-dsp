#ifndef PULSED_WAVEFORM_H
#define PULSED_WAVEFORM_H
#include "Waveform.h"
class PulsedWaveform : public Waveform {
 public:
  double prf() const { return d_prf; }
  double pulsewidth() const { return d_pulsewidth; }

 protected:
  // Pulse repetition frequency (Hz)
  double d_prf;
  // Pulse width (s)
  double d_pulsewidth;
};
#endif