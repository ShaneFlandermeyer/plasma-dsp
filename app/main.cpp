#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "barkercode.h"
#include "linearfmwaveform.h"
#include "phasecode.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "utils.h"
#include "window.h"

using namespace matplot;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 130e-6;
  std::vector<double> prf = {1e3};
  auto sampRate = 20e6;
  auto wave = BarkerCode(13, 10e-6, prf, sampRate);
  auto pulse = wave.pulseTrain();
  auto real = std::vector<double>(pulse.size());
  std::transform(pulse.begin(), pulse.end(), real.begin(),
                 [](auto x) { return std::real(x); });

  plot(real);
  show();
  return 0;
}