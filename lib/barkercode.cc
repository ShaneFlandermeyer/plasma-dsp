#include "barkercode.h"

BarkerCode::BarkerCode() {
  d_nChips = 0;
  d_chipwidth = 0;
  d_code = std::vector<double>();
}

std::vector<std::complex<double>> BarkerCode::pulse() {
  return PhaseCodedWaveform::pulse();
}

std::vector<std::complex<double>> BarkerCode::step() {
  return PulsedWaveform::step();
}