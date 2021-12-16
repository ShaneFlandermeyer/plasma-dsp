#include "barkercode.h"

#include <iostream>
BarkerCode::BarkerCode() {}

BarkerCode::BarkerCode(int n)
    : PhaseCodedWaveform(n, 0, PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform() {}

BarkerCode::BarkerCode(int n, double chipwidth, double prf, double sampRate)
    : Waveform(sampRate),
      PhaseCodedWaveform(n, chipwidth,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform(n * chipwidth, prf) {}

BarkerCode::BarkerCode(int n, double chipwidth, std::vector<double> prf,
                       double sampRate)
    : Waveform(sampRate),
      PhaseCodedWaveform(n, chipwidth,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform(n * chipwidth, prf) {

  auto eps = std::numeric_limits<double>::epsilon();
  auto temp = sampRate * chipwidth;
  if (std::abs(temp - std::round(temp)) > 1e-10) {
    throw std::invalid_argument("The number of samples per chip must be an integer.");
  }
}