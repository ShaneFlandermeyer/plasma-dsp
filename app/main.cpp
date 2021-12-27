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
  auto pulse_mat = Matrix2D<std::complex<double>>(wave.size(), 1, wave);
  auto mf = lfm.MatchedFilter();

  // auto mat = Matrix2D<std::complex<double>>(5,5,std::vector<std::complex<double>>(25,5));
  // auto vec = std::vector<std::complex<double>>(5,1);
  auto mf_resp = MatchedFilter(pulse_mat,mf);
  std::vector<std::complex<double>> dat(mf_resp.numel());
  for (int i = 0; i < mf_resp.numel(); i++) {
    dat[i] = mf_resp(i,0);
  }
  // auto dat = std::vector<std::complex<double>>(mf_resp.data());
  plot(db(abs(dat)));
  show();
  return 0;
}