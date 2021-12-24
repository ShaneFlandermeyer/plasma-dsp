#include "phasecodedwaveform.h"

#include <iostream>
#include <limits>

namespace plasma {

std::vector<std::complex<double>> PhaseCodedWaveform::sample() {
  // Oversampling factor
  int num_samps_chip = std::round(d_chipwidth * samp_rate());
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
  d_chipwidth = 0;
  d_code = std::vector<double>();
}

PhaseCodedWaveform::PhaseCodedWaveform(int num_chips, double chipwidth,
                                       std::vector<double> code) {
  d_num_chips = num_chips;
  d_chipwidth = chipwidth;
  d_code = code;

  // Check that the number of samples per chip is an integer
  auto eps = std::numeric_limits<double>::epsilon();
  auto temp = d_samp_rate * chipwidth;
  if (std::abs(temp - std::round(temp)) > 1e-10) {
    throw std::invalid_argument(
        "The number of samples per chip must be an integer.");
  }
}
}  // namespace plasma