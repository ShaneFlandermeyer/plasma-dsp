#include "fmcw-waveform.h"

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

Eigen::ArrayXcd FMCWWaveform::sample() {
  size_t num_samps_sweep = d_sweep_time * d_samp_rate;
  double ts = 1 / samp_rate();
  Eigen::ArrayXcd out(num_samps_sweep);
  // Compute sample times
  // TODO: Is this actually right?
  Eigen::ArrayXd t(num_samps_sweep, ts);
  t(0) = 0;
  std::partial_sum(t.begin(), t.end(), t.begin());
  // If the sweep direction is UP (1), the frequency increases over the
  // interval. If the sweep direction is DOWN (-1), the frequency decreases
  // over the interval
  // TODO: Vectorize this with elementwise multiplications
  for (int i = 0; i < num_samps_sweep; i++) {
    // If the sweep direction is UP (1), the frequency increases over the
    // interval. If the sweep direction is DOWN (-1), the frequency decreases
    // over the interval
    out[i] = std::exp((double)d_sweep_direction * Im * M_PI *
                      d_sweep_bandwidth * pow(i * ts, 2) / d_sweep_time);
    // By default, the waveform sweeps over the POSITIVE (0) interval
    // [0,bandwidth]. If a SYMMETRIC (1) sweep is chosen, apply a frequency
    // shift to move the spectrum in the interval [-bandwidth,bandwidth]
    out[i] *= std::exp((double)d_sweep_interval * Im * 2.0 * M_PI *
                       -d_sweep_bandwidth / 2.0 * (double)i / samp_rate());
  }

  return out;
}

std::vector<std::complex<double>>
FMCWWaveform::demod(std::vector<std::complex<double>> &in) {
  auto ref = sample();
  std::vector<std::complex<double>> out(in.size());
  std::transform(in.begin(), in.end(), ref.begin(), out.begin(),
                 [](std::complex<double> a, std::complex<double> b) {
                   return conj(a) * b;
                 });
  return out;
}

} // namespace plasma