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
#include "matrix2d.h"
#include "rangedoppler.h"

using namespace matplot;
using namespace plasma;
int main() {
  auto bandwidth = 10e6;
  auto pulse_width = 10e-6;
  auto samp_rate = 20e6;
  std::vector<double> prf = {1e3};
  auto lfm = LinearFMWaveform(bandwidth, pulse_width, prf, samp_rate);
  auto wave = lfm.waveform();
  

  auto mat = Matrix2D<std::complex<double>>(5,5);
  MatchedFilter(mat,wave);


  return 0;
}