#ifndef B50A8067_E867_4FD6_AE82_CDA1990F0971
#define B50A8067_E867_4FD6_AE82_CDA1990F0971

#include "waveform.h"

namespace plasma {

class FMCWWaveform : public Waveform {
 protected:
  double d_sweep_time;
  double d_sweep_bandwidth;
  std::vector<std::complex<double>> sample() override;

 public:
  FMCWWaveform() = default;
  FMCWWaveform(double sweep_time, double sweep_bandwidth, double samp_rate);
};
}  // namespace plasma
#endif /* B50A8067_E867_4FD6_AE82_CDA1990F0971 */
