#ifndef SQUARE_WAVE_H
#define SQUARE_WAVE_H
#include "PulsedWaveform.h"
class SquareWaveform : public PulsedWaveform {
  public:
    std::vector<std::complex<double>> sample();
    // Constructors and destructors
    SquareWaveform();
    SquareWaveform(double pulsewidth, double prf, double sampRate);
    ~SquareWaveform();
};
#endif
