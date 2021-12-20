#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "barkercode.h"
#include "linearfmwaveform.h"
#include "phasecode.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "pcfm.h"
#include "utils.h"
#include "window.h"

using namespace matplot;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  std::vector<double> prf = {1e3};
  auto sampRate = 20e6;
  auto code = PhaseCode::generate_code(PhaseCode::BARKER, 13);
  auto filter = window::rectangular(3);
  auto pcfm = PCFMWaveform(code, filter);
  // auto pulse = wave.pulse();
  // auto real = std::vector<double>(pulse.size());
  // std::transform(pulse.begin(), pulse.end(), real.begin(),
  //                [](auto x) { return std::real(x); });

  // plot(real);
  // show();
  return 0;
}