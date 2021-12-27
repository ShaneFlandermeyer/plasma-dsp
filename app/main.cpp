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
  auto bandwidth = 300;
  auto pulse_width = 2;
  auto samp_rate = 1/0.001;
  std::vector<double> prf = {10e3};
  auto wave = LinearFMWaveform(bandwidth, pulse_width, prf, samp_rate);
  wave.freq_offset(150);
  auto x = wave.waveform();
  // auto win = hamming(256);
  auto spec = transpose(spectrogram(x,hamming(256),256,250));
  spec = db(spec);
  image(0,pulse_width,-samp_rate/2,samp_rate/2,spec,true);
  gca()->y_axis().reverse(false);
  show();
  // colorbar();
  // xlabel("Time (s)");

  return 0;
}