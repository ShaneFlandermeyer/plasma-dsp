#include "barker_coded_waveform.h"

#include <iostream>

namespace plasma {
BarkerCode::BarkerCode() {}

BarkerCode::BarkerCode(int n)
    : PhaseCodedWaveform(n, 0, PhaseCode::generate_code(PhaseCode::BARKER, n)) {}

BarkerCode::BarkerCode(int n, double chip_width, double prf, double samp_rate)
    : Waveform(samp_rate),
      PhaseCodedWaveform(n, chip_width,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)) {}

BarkerCode::BarkerCode(int n, double chip_width, Eigen::ArrayXd prf,
                       double samp_rate)
    : Waveform(samp_rate),
      PhaseCodedWaveform(n, chip_width,
                         PhaseCode::generate_code(PhaseCode::BARKER, n)) {
}
}  // namespace plasma