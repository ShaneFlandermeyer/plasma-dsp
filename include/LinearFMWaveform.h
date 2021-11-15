#ifndef LINEARFMWAVEFORM_H
#define LINEARfMWAVEFORM_H

#include "Waveform.h"

class LinearFMWaveform: public Waveform {
  public:
    double bandwidth;
    double pulsewidth;
    double sampRate;
    double prf;
    
};

#endif