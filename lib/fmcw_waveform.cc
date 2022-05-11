#include "fmcw_waveform.h"
#include <iostream>
namespace plasma {

FMCWWaveform::FMCWWaveform(double sweep_time, double sweep_bandwidth,
                           double samp_rate, SweepInterval interval,
                           SweepDirection direction)
    : Waveform(samp_rate) {
  d_sweep_time = sweep_time;
  d_sweep_bandwidth = sweep_bandwidth;
  d_sweep_interval = interval;
  d_sweep_direction = direction;
}

Eigen::ArrayXcd FMCWWaveform::step() {
  Eigen::ArrayXcd samples = sample();
  FrequencyShift(samples, d_freq_offset);
  return samples;
}

Eigen::ArrayXcd FMCWWaveform::sample() {
  size_t num_samps = round(d_samp_rate * d_sweep_time);
  double ts = 1 / d_samp_rate;
  Eigen::ArrayXcd out(num_samps);
  Eigen::ArrayXd t =
      Eigen::ArrayXd::LinSpaced(num_samps, 0, num_samps - 1) * ts;
  // If the sweep direction is UP (1), the frequency increases over the
  // interval. If the sweep direction is DOWN (-1), the frequency decreases
  // over the interval
  double beta = d_sweep_bandwidth / d_sweep_time;
  if (d_sweep_direction == UP) {
    if (d_sweep_interval == POSITIVE) {
      out = exp(Im * M_PI * beta * t.square());
    } else {
      out = exp(Im * M_PI * beta * t * (t - d_sweep_time));
    }
  } else if (d_sweep_direction == DOWN) {
    if (d_sweep_interval == POSITIVE) {
      out = exp(Im * M_PI * beta * t * (2 * d_sweep_time - t));
    } else {
      out = exp(Im * M_PI * beta * t * (d_sweep_time - t));
    }
  }
  return out;
}

Eigen::ArrayXcd FMCWWaveform::demod(Eigen::ArrayXcd &in) {
  auto ref = sample();
  return conj(in) * ref;
}

} // namespace plasma