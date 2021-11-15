#ifndef LINEAR_FM_WAVEFORM_H
#define LINEAR_FM_WAVEFORM_H

#include "PulsedWaveform.h"
#include "Waveform.h"
class LinearFMWaveform : public PulsedWaveform {
 protected:
  // Sweep bandwidth (Hz)
  double d_bandwidth;

 public:
  // Return a vector containing the waveform samples for one PRI
  std::vector<std::complex<double>> sample();
  // Getters and setters
  double bandwidth() const { return d_bandwidth; }
  void bandwidth(double bandwidth) { d_bandwidth = bandwidth; }

  // Constructors and destructors
  LinearFMWaveform();
  LinearFMWaveform(double bandwidth, double pulsewidth, double prf,
                   double sampRate);
  ~LinearFMWaveform();
};

#endif