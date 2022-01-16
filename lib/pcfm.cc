#include "pcfm.h"

#include <iostream>

namespace plasma {

// PCFMWaveform::PCFMWaveform() {
//   d_code = std::vector<double>();
//   d_filter = std::vector<double>();
// }

PCFMWaveform::PCFMWaveform(const Eigen::ArrayXd &code,
                           const Eigen::ArrayXd &filter, double samp_rate,
                           double prf) {
  d_code = code;
  d_filter = filter;
  d_samp_rate = samp_rate;
  d_prf = Eigen::ArrayXd(1);
  d_prf(0) = prf;
}

Eigen::ArrayXcd PCFMWaveform::sample() {
  Eigen::ArrayXd difference = ComputePhaseChange();
  Eigen::ArrayXd impulse_train = oversample(difference, d_filter.size());
  // Apply the shaping filter
  Eigen::ArrayXd chi = filter(impulse_train, d_filter);
  Eigen::ArrayXd phase = cumsum(chi);
  Eigen::ArrayXcd out = exp(Im * phase);
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
  for (size_t i = 0; i < in.size(); i++)
    out(i * factor) = in(i);
  return out;
}

inline Eigen::ArrayXd PCFMWaveform::filter(const Eigen::ArrayXd &in,
                                           const Eigen::ArrayXd &filter) {

  // Pad the filter to the size of the input
  Eigen::ArrayXd pad_filter = Eigen::ArrayXd::Zero(in.size());
  size_t filter_size = std::min(in.size(), filter.size());
  pad_filter.head(filter_size) = filter.head(filter_size);
  // Apply the filter via an FFT
  Eigen::FFT<double> fft;
  Eigen::VectorXcd in_fft = fft.fwd(in.matrix().eval());
  Eigen::VectorXcd filter_fft = fft.fwd(pad_filter.matrix().eval());
  Eigen::VectorXd out = fft.inv(in_fft.cwiseProduct(filter_fft).eval());
  return out.array();
}

inline Eigen::ArrayXd PCFMWaveform::cumsum(const Eigen::ArrayXd &in) {
  Eigen::ArrayXd out(in.size());
  std::partial_sum(in.begin(), in.end(), out.begin());
  return out;
}

} // namespace plasma