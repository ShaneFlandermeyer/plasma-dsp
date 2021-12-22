#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "barkercode.h"
#include "linearfmwaveform.h"
#include "pcfm.h"
#include "phasecode.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "vector-utils.h"
#include "signal-processing.h"
#include "window.h"

using namespace matplot;
using namespace plasma;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  auto sampRate = 20e6;
  std::vector<double> prf = {10e3};
  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  auto code = PhaseCode::generate_code(PhaseCode::FRANK, 16);
  auto pcw = std::vector<std::complex<double>>(code.size());
  std::transform(code.begin(), code.end(), pcw.begin(),
                 [](auto x) { return exp(Im * x); });
  auto autocorr = abs(conv(pcw, conj(pcw)));
  // std::vector<std::complex<double>> pulse2;
  plot(autocorr);
  show();

  return 0;
}