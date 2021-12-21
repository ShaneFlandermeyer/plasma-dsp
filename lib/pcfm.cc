#include "pcfm.h"

#include <iostream>

#include "utils.h"

PCFMWaveform::PCFMWaveform() {
  d_code = std::vector<double>();
  d_filter = std::vector<double>();
}

PCFMWaveform::PCFMWaveform(const std::vector<double>& code,
                           const std::vector<double>& filter) {
  d_code = code;
  d_filter = filter;
  // Phase difference vector
  auto diff = std::vector<double>(code.size());
  // Number of samples per chip
  auto nSampsChip = filter.size();
  // Oversampled phase code difference vector
  auto alpha = std::vector<double>(code.size() * nSampsChip);
  // Phase vector
  auto phase = std::vector<double>(alpha.size());
  // Waveform vector
  d_waveform = std::vector<std::complex<double>>(alpha.size());
  // FIXME: Assumes values are in range [-pi, pi]
  std::adjacent_difference(code.begin(), code.end(), diff.begin());
  for (int i = 0; i < diff.size(); i++) alpha[i * nSampsChip] = diff[i];
  // Convolve phase difference code with shaping filter
  auto alphaFilt = conv(alpha, filter);
  // Integrate frequency back to phase
  std::partial_sum(alphaFilt.begin(), alphaFilt.end(), phase.begin(),
                   std::plus<double>());
  // Take complex exponential of the phase vector
  std::transform(phase.begin(), phase.end(), d_waveform.begin(),
                 [](auto x) { return std::exp(Im * x); });
}

std::vector<std::complex<double>> PCFMWaveform::pulse() {
  // TODO: Update the waveform whenever the code or filter changes
  return d_waveform;
}