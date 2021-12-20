#include "pcfm.h"
#include <iostream>
PCFMWaveform::PCFMWaveform() {
  d_code = std::vector<double>();
  d_filter = std::vector<double>();

}

PCFMWaveform::PCFMWaveform(const std::vector<double>& code, const std::vector<double>& filter) {
  d_code = code;
  d_filter = filter;
  // Phase difference code
  auto alpha = std::vector<double>(code.size());
  std::adjacent_difference(code.begin(), code.end(), alpha.begin());
}

std::vector<std::complex<double>> PCFMWaveform::pulse() {
  return std::vector<std::complex<double>>();
}