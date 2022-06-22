#include "pcfm.h"

#include <iostream>

namespace plasma {

PCFMWaveform::PCFMWaveform(const Eigen::ArrayXd &code,
                           const Eigen::ArrayXd &filter, double samp_rate,
                           double prf)
    : Waveform(samp_rate),
      PulsedWaveform(filter.size() * code.size() / samp_rate, prf),
      d_code(code), d_filter(filter) {}

Eigen::ArrayXcd PCFMWaveform::sample() {
  // From the input phase code, the first order derivative phase
  // difference code (bounded between [-pi,pi]) is computed. This code is then
  // "oversampled" to prepare it for the shaping filter by appending N zeros
  // after every code value, where N is the number of samples in the filter.
  // After applying the filter, the smoothed first order phase derivative is
  // integrated back to phase and applied to a complex exponential to get the
  // final waveform samples
  Eigen::ArrayXd difference = ComputePhaseChange();
  Eigen::ArrayXd train = oversample(difference, d_filter.size());
  Eigen::ArrayXd freq = plasma::filter(d_filter, train);
  Eigen::ArrayXd phase = cumsum(freq);
  Eigen::ArrayXcd out = exp(plasma::Im * phase);
  return out;
}

inline Eigen::ArrayXd PCFMWaveform::ComputePhaseChange() {
  // Compute the differences that are not wrapped around pi
  Eigen::ArrayXd difference(d_code.size());
  std::adjacent_difference(d_code.begin(), d_code.end(), difference.begin());
  // Wrap each element to [-pi, pi]
  for (size_t i = 0; i < difference.size(); i++)
    if (std::abs(difference(i)) > M_PI)
      difference(i) -= 2 * M_PI * difference.sign()(i);
  return difference;
}

inline Eigen::ArrayXd PCFMWaveform::oversample(const Eigen::ArrayXd &in,
                                               size_t factor) {
  Eigen::ArrayXd out = Eigen::ArrayXd::Zero(in.size() * factor);
  out(Eigen::seqN(0, in.size(), factor)) = in;
  return out;
}

inline Eigen::ArrayXd PCFMWaveform::cumsum(const Eigen::ArrayXd &in) {
  Eigen::ArrayXd out(in.size());
  std::partial_sum(in.begin(), in.end(), out.begin());
  return out;
}

} // namespace plasma