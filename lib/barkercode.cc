#include "plasma-dsp/barkercode.h"

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
      PulsedWaveform(n * chipwidth, prf) {}

std::vector<std::complex<double>> BarkerCode::pulse() {
  return PhaseCodedWaveform::pulse();
}

std::vector<std::complex<double>> BarkerCode::pulseTrain() {
  return PulsedWaveform::pulseTrain();
}