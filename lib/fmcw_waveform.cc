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

af::array FMCWWaveform::sample() {
  size_t num_samp_sweep = round(d_samp_rate * d_sweep_time);
  double ts = 1 / d_samp_rate;
  af::array out(num_samp_sweep, c64);
  af::array t = af::range(af::dim4(num_samp_sweep), -1, f64) * ts;
  // If the sweep direction is UP (1), the frequency increases over the
  // interval. If the sweep direction is DOWN (-1), the frequency decreases
  // over the interval
  double beta = d_sweep_bandwidth / d_sweep_time;
  if (d_sweep_direction == UP) { // Upsweep
    if (d_sweep_interval == POSITIVE) { // Sweep from [0,B]
      out = exp(af::Im * M_PI * beta * af::pow(t, 2));
    } else { // Sweep from [-B/2,B/2]
      out = exp(af::Im * M_PI * beta * t * (t - d_sweep_time));
    }
  } else if (d_sweep_direction == DOWN) { // Downsweep
    if (d_sweep_interval == POSITIVE) { // Sweep from [0,B]
      out = exp(af::Im * M_PI * beta * t * (2 * d_sweep_time - t));
    } else { // Sweep from [-B/2,B/2]
      out = exp(af::Im * M_PI * beta * t * (d_sweep_time - t));
    }
  }
  return out;
}

af::array FMCWWaveform::step() {
  // This currently just returns a single sweep, but it will eventually be used
  // to get an arbitrary number of sweeps
  af::array samples = sample();
  return samples;
}

af::array FMCWWaveform::demod(const af::array &in) {
  auto ref = sample();
  return af::conjg(in) * ref;
}

} // namespace plasma