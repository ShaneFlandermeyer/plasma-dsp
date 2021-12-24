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
  auto x = wave.pulse();
  auto win = rectangular(128);
  auto spec = spectrogram(x,win,128,120);

  image(spec,true);
  show();

  return 0;
}