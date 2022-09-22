#include "phase_coded_waveform.h"

#include <iostream>
#include <limits>

namespace plasma {

af::array PhaseCodedWaveform::sample() {
  // Repeat each element in the phase code vector num_samp_chip times
  size_t num_samp_chip = round(d_chip_width * d_samp_rate);
  af::array out(d_code.elements() * num_samp_chip, c64);
  for (auto i = 0; i < num_samp_chip; i++) {
    out(af::seq(i, d_code.elements() * num_samp_chip - 1, num_samp_chip)) =
        exp(af::Im * d_code);
  }
  return out;
}

PhaseCodedWaveform::PhaseCodedWaveform() {
  d_num_chips = 0;
  d_chip_width = 0;
}

PhaseCodedWaveform::PhaseCodedWaveform(const af::array &code, double chip_width,
                                       double prf, double samp_rate)
    : PulsedWaveform(code.elements() * chip_width, prf), Waveform(samp_rate),
      d_code(code.as(f64)), d_chip_width(chip_width),
      d_num_chips(code.elements()) {

  // Check that the number of samples per chip is an integer
  auto temp = d_samp_rate * chip_width;
  if (std::abs(temp - std::round(temp)) > 1e-10) {
    throw std::invalid_argument(
        "The number of samples per chip must be an integer.");
  }
}

PhaseCodedWaveform::PhaseCodedWaveform(af::array code, double chip_width,
                                       std::vector<double> prf,
                                       double samp_rate)
    : PulsedWaveform(code.elements() * chip_width, prf), Waveform(samp_rate),
      d_code(code, f64), d_chip_width(chip_width),
      d_num_chips(code.elements()) {
  // Check that the number of samples per chip is an integer
  auto temp = d_samp_rate * chip_width;
  if (std::abs(temp - std::round(temp)) > 1e-10) {
    throw std::invalid_argument(
        "The number of samples per chip must be an integer.");
  }
}

} // namespace plasma