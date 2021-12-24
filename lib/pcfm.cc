#include "pcfm.h"

namespace plasma {

PCFMWaveform::PCFMWaveform() {
  d_code = std::vector<double>();
  d_filter = std::vector<double>();
}

PCFMWaveform::PCFMWaveform(const std::vector<double>& code,
                           const std::vector<double>& filter) {
  // Normalize the shaping filter to integrate to unity
  // TODO: Use decltype(filter)::value_type(0) instead of 0.0
  auto sum = std::accumulate(filter.begin(), filter.end(), 0.0);
  d_filter = std::vector<double>(filter.size());
  std::transform(filter.begin(), filter.end(), d_filter.begin(),
                 [sum](const auto& x) { return x / sum; });
  d_code = code;

  // Phase difference vector
  auto diff = std::vector<double>(d_code.size());
  // Number of samples per chip
  auto num_samps_chip = d_filter.size();
  // Oversampled phase code difference vector
  auto alpha = std::vector<double>(d_code.size() * num_samps_chip);
  // Phase vector
  auto phase = std::vector<double>(alpha.size());
  // Waveform vector
  d_waveform = std::vector<std::complex<double>>(alpha.size());
  // FIXME: Assumes values are in range [-pi, pi]
  std::adjacent_difference(d_code.begin(), d_code.end(), diff.begin());
  for (int i = 0; i < diff.size(); i++) alpha[i * num_samps_chip] = diff[i];
  // Convolve phase difference code with shaping filter
  auto one = std::vector<double>(1,1);
  auto alpha_filt = plasma::filter(filter, one, alpha);
  // Integrate frequency back to phase
  std::partial_sum(alpha_filt.begin(), alpha_filt.end(), phase.begin(),
                   std::plus<double>());
  // Take complex exponential of the phase vector
  std::transform(phase.begin(), phase.end(), d_waveform.begin(),
                 [](auto x) { return std::exp(Im * x); });
}

std::vector<std::complex<double>> PCFMWaveform::sample() {
  // TODO: Update the waveform whenever the code or filter changes
  return d_waveform;
}
}  // namespace plasma