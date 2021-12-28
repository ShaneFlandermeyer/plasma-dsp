#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "barkercode.h"
#include "linearfmwaveform.h"
#include "matrix2d.h"
#include "pcfm.h"
#include "phasecode.h"
#include "rangedoppler.h"
#include "signal-processing.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "vector-utils.h"
#include "window.h"

using namespace matplot;
using namespace plasma;
int main() {
  auto bandwidth = 10e6;
  auto pulse_width = 10e-6;
  auto samp_rate = 20e6;
  std::vector<double> prf = {1e3};
  auto lfm = LinearFMWaveform(bandwidth, pulse_width, prf, samp_rate);
  auto wave = lfm.waveform();

  auto mf = lfm.MatchedFilter();
  auto num_pulses = 32;
  auto pulse_mat =
      Matrix2D<std::complex<double>>(wave.size(), num_pulses, wave);
  // For testing, just make num_pulses copy of the input waveform
  // In practice this will be filled as we collect data
  for (auto i_pulse = 1; i_pulse < num_pulses; i_pulse++)
    for (auto i_sample = 0; i_sample < wave.size(); i_sample++)
      pulse_mat(i_sample, i_pulse) = wave[i_sample];

  auto rd_map = RangeDopplerMap(pulse_mat,mf);
  auto rd_map_vec = std::vector<std::vector<double>>(rd_map.rows(), std::vector<double>(rd_map.cols()));
  for (auto i_row = 0; i_row < rd_map.rows(); i_row++)
    for (auto i_col = 0; i_col < rd_map.cols(); i_col++)
      rd_map_vec[i_row][i_col] = 10*log10(abs(rd_map(i_row, i_col)));
  image(rd_map_vec, true);
  show();
  return 0;
}