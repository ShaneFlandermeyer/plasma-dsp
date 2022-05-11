#include "phase_coded_waveform.h"

#include <iostream>
#include <limits>

namespace plasma {

Eigen::ArrayXcd PhaseCodedWaveform::sample() {
  // Oversampling factor
  size_t num_samps_chip = round(d_chip_width * d_samp_rate);
  size_t num_samps_out = num_samps_chip * d_num_chips;
  // Repeat each element in the phase code vector num_samps_chip times
  Eigen::ArrayXcd out = exp(Im * d_code(Eigen::VectorXi::LinSpaced(
                                     num_samps_out, 0, d_code.size() - 1)));
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