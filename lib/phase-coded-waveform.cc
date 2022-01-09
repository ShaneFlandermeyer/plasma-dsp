#include "phase-coded-waveform.h"

#include <iostream>
#include <limits>

namespace plasma {

std::vector<std::complex<double>> PhaseCodedWaveform::sample() {
  // Oversampling factor
  int num_samps_chip = std::round(d_chip_width * samp_rate());
  std::vector<std::complex<double>> pulse(num_samps_chip * d_num_chips);
  // Create the oversampled waveform vector
  for (int i = 0; i < d_code.size(); i++) {
    std::fill(pulse.begin() + i * num_samps_chip,
              pulse.begin() + (i + 1) * num_samps_chip,
              std::exp(Im * d_code[i]));
  }
  return pulse;
}

PhaseCodedWaveform::PhaseCodedWaveform() {
  d_num_chips = 0;
  d_chip_width = 0;
  d_code = std::vector<double>();
}

PhaseCodedWaveform::PhaseCodedWaveform(int num_chips, double chip_width,
                                       std::vector<double> code) {
  d_num_chips = num_chips;
  d_chip_width = chip_width;
  d_code = code;

  // Check that the number of samples per chip is an integer
  auto eps = std::numeric_limits<double>::epsilon();
  auto temp = d_samp_rate * chip_width;
  if (std::abs(temp - std::round(temp)) > 1e-10) {
    throw std::invalid_argument(
        "The number of samples per chip must be an integer.");
  }
}
}  // namespace plasma