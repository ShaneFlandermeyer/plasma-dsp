#include "barkercode.h"

#include <iostream>

namespace plasma {
BarkerCode::BarkerCode() {}

BarkerCode::BarkerCode(int n)
    : PhaseCodedWaveform(n, 0, PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform() {}

BarkerCode::BarkerCode(int n, double chipwidth, double prf, double samp_rate)
    : Waveform(samp_rate),
      PhaseCodedWaveform(n, chipwidth,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform(n * chipwidth, prf) {}

BarkerCode::BarkerCode(int n, double chipwidth, std::vector<double> prf,
                       double samp_rate)
    : Waveform(samp_rate),
      PhaseCodedWaveform(n, chipwidth,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)),
      PulsedWaveform(n * chipwidth, prf) {
}
}  // namespace plasma