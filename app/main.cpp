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
  auto pulse_width = 100e-6;
  auto samp_rate = 20e6;
  std::vector<double> prf = {10e3};
  auto wave = LinearFMWaveform(bandwidth, pulse_width, prf, samp_rate);
  auto x = wave.pulse();
  auto win = rectangular(128);
  auto spec = spectrogram(x,win,128,120);
  image(transpose(spec),true);
  xlabel("Time (s)");
  show();

  return 0;
}