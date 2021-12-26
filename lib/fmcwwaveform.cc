#include "fmcwwaveform.h"

namespace plasma {

std::vector<std::complex<double>> FMCWWaveform::sample() {
  // TODO: Implement me
  return std::vector<std::complex<double>>();
}

FMCWWaveform::FMCWWaveform(double sweep_time, double sweep_bandwidth,
                           double samp_rate)
    : Waveform(samp_rate) {
  d_sweep_time = sweep_time;
  d_sweep_bandwidth = sweep_bandwidth;
}
}  // namespace plasma