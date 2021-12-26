#include "fmcwwaveform.h"

namespace plasma {

std::vector<std::complex<double>> FMCWWaveform::sample() {
  // TODO: Incorporate the sweep interval and direction parameters into this
  int num_samps_sweep = d_sweep_time * d_samp_rate;
  std::vector<std::complex<double>> out(num_samps_sweep);
  auto ts = 1 / samp_rate();
  for (int i = 0; i < num_samps_sweep; i++) {
    out[i] = std::exp((double)d_sweep_direction * Im * M_PI *
                      d_sweep_bandwidth * pow(i * ts, 2) / d_sweep_time);
  }

  return out;
}

FMCWWaveform::FMCWWaveform(double sweep_time, double sweep_bandwidth,
                           double samp_rate, SweepInterval interval,
                           SweepDirection direction)
    : Waveform(samp_rate) {
  d_sweep_time = sweep_time;
  d_sweep_bandwidth = sweep_bandwidth;
  d_sweep_interval = interval;
  d_sweep_direction = direction;
}
}  // namespace plasma