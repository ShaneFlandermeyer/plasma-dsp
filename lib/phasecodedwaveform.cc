#include "phasecodedwaveform.h"

std::vector<std::complex<double>> PhaseCodedWaveform::pulse() {
  return std::vector<std::complex<double>>();
}

PhaseCodedWaveform::PhaseCodedWaveform() {
  d_nChips = 0;
  d_chipwidth = 0;
  d_code = std::vector<double>();
}

PhaseCodedWaveform::PhaseCodedWaveform(int nChips, double chipwidth,
                                       std::vector<double> code) {
  d_nChips = nChips;
  d_chipwidth = chipwidth;
  d_code = code;
}