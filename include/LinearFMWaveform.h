#ifndef LINEARFMWAVEFORM_H
#define LINEARfMWAVEFORM_H

#include "Waveform.h"
#include "PulsedWaveform.h"
class LinearFMWaveform: public PulsedWaveform {
  public:
    double bandwidth;
    double pulsewidth;
    double sampRate;
    std::vector<std::complex<float>> sample();
    LinearFMWaveform();
    LinearFMWaveform(double bandwidth, double pulsewidth, double prf, double sampRate);
    ~LinearFMWaveform();
};



#endif