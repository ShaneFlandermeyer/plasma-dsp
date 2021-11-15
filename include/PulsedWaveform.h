#ifndef PULSEDWAVEFORM_H
#define PULSEDWAVEFORM_H
#include "Waveform.h"
class PulsedWaveform: public Waveform {
  public:
    // Pulse repetition frequency (Hz)
    double prf;
    // Pulse width (s)
    double pulsewidth;
};
#endif