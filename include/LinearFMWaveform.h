#ifndef LINEAR_FM_WAVEFORM_H
#define LINEAR_FM_WAVEFORM_H

#include "Waveform.h"
#include "PulsedWaveform.h"
class LinearFMWaveform: public PulsedWaveform {
  public:
    // Sweep bandwidth (Hz)
    double bandwidth;
    
    std::vector<std::complex<float>> sample();
    LinearFMWaveform();
    LinearFMWaveform(double bandwidth, double pulsewidth, double prf, double sampRate);
    ~LinearFMWaveform();
};



#endif