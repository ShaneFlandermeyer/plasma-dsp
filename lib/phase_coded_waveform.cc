#include "phase_coded_waveform.h"

#include <iostream>
#include <limits>

namespace plasma {

Eigen::ArrayXcd PhaseCodedWaveform::sample() {
  // Oversampling factor
  size_t num_samps_chip = std::round(d_chip_width * samp_rate());
  Eigen::ArrayXcd out = Eigen::ArrayXcd::Zero(num_samps_chip * d_num_chips);
  // Create the oversampled waveform vector
  for (int i = 0; i < d_code.size(); i++) {
    out(Eigen::seqN(i * num_samps_chip, num_samps_chip)) =
        exp(Im * d_code[i] * Eigen::ArrayXcd::Ones(num_samps_chip));
  }
  return out;
}

PhaseCodedWaveform::PhaseCodedWaveform() {
  d_num_chips = 0;
  d_chip_width = 0;
}

PhaseCodedWaveform::PhaseCodedWaveform(Eigen::ArrayXd code, double chip_width,
                                       double prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(code.size() * chip_width, prf) {
  d_num_chips = code.size();
  d_chip_width = chip_width;
  d_code = code;

  // Check that the number of samples per chip is an integer
  auto temp = d_samp_rate * chip_width;
  if (std::abs(temp - std::round(temp)) > 1e-10) {
    throw std::invalid_argument(
        "The number of samples per chip must be an integer.");
  }
}

PhaseCodedWaveform::PhaseCodedWaveform(Eigen::ArrayXd code, double chip_width,
                                       Eigen::ArrayXd prf, double samp_rate)
    : Waveform(samp_rate), PulsedWaveform(code.size() * chip_width, prf) {
  d_num_chips = code.size();
  d_chip_width = chip_width;
  d_code = code;

  // Check that the number of samples per chip is an integer
  auto temp = d_samp_rate * chip_width;
  if (std::abs(temp - std::round(temp)) > 1e-10) {
    throw std::invalid_argument(
        "The number of samples per chip must be an integer.");
  }
}

} // namespace plasma