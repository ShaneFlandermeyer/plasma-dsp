#ifndef LINEAR_FM_WAVEFORM_H
#define LINEAR_FM_WAVEFORM_H

#include "PulsedWaveform.h"
#include "Waveform.h"
class LinearFMWaveform : public PulsedWaveform {
 public:
  // Sweep bandwidth (Hz)
  double bandwidth() const { return d_bandwidth; }

  std::vector<std::complex<double>> sample();
  LinearFMWaveform();
  LinearFMWaveform(double bandwidth, double pulsewidth, double prf,
                   double sampRate);
  ~LinearFMWaveform();

 protected:
  double d_bandwidth;
};

#endif