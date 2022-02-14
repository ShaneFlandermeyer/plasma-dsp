#include "fmcw_waveform.h"

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

Eigen::ArrayXcd FMCWWaveform::sample(double t1 = -1, double t2 = -1) {
  if (t1 == -1) t1 = 0;
  if (t2 == -1) t2 = sweep_time();
  size_t num_samps = static_cast<int>(samp_rate() * (t2 - t1));
  double ts = 1 / samp_rate();
  Eigen::ArrayXcd out(num_samps);
  Eigen::ArrayXd t =
      Eigen::ArrayXd::LinSpaced(num_samps, 0, num_samps-1) * ts + t1;
  // If the sweep direction is UP (1), the frequency increases over the
  // interval. If the sweep direction is DOWN (-1), the frequency decreases
  // over the interval
  out = exp((double)d_sweep_direction * Im * M_PI * d_sweep_bandwidth *
            t.square() / (t2-t1));
  // By default, the waveform sweeps over the POSITIVE (0) interval
  // [0,bandwidth]. If a SYMMETRIC (1) sweep is chosen, apply a frequency
  // shift to move the spectrum in the interval [-bandwidth,bandwidth]
  out = out * exp((double)d_sweep_interval * Im * 2.0 * M_PI * -d_sweep_bandwidth /
             2.0 * t);

  return out;
}

Eigen::ArrayXcd FMCWWaveform::demod(Eigen::ArrayXcd &in) {
  auto ref = sample(0, d_sweep_time);
  return conj(in) * ref;
}

} // namespace plasma