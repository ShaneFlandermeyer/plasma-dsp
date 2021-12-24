#include "barkercode.h"

#include <iostream>

namespace plasma {
BarkerCode::BarkerCode() {}

BarkerCode::BarkerCode(int n)
    : PhaseCodedWaveform(n, 0, PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform() {}

BarkerCode::BarkerCode(int n, double chip_width, double prf, double samp_rate)
    : Waveform(samp_rate),
      PhaseCodedWaveform(n, chip_width,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform(n * chip_width, prf) {}

BarkerCode::BarkerCode(int n, double chip_width, std::vector<double> prf,
                       double samp_rate)
    : Waveform(samp_rate),
      PhaseCodedWaveform(n, chip_width,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform(n * chip_width, prf) {
}
}  // namespace plasma