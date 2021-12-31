#include <matplot/matplot.h>

#include "cfar.h"
#include "linearfmwaveform.h"
#include "rangedoppler.h"

using namespace plasma;
using namespace matplot;
int main() {
  // Generate the waveform and matched filter
  auto lfm = LinearFMWaveform(10e6, 10e-6, 1e3, 20e6);
  auto wave = lfm.waveform();
  auto mf = lfm.MatchedFilter();
  // Generate a fast-time slow-time matrix
  // TODO: Simulate this for targets with nonzero range and doppler
  auto num_pulses_cpi = 64;
  auto cpi_matrix = Matrix2D<std::complex<double>>(wave.size(), num_pulses_cpi);
  for (int i_pulse = 0; i_pulse < num_pulses_cpi; i_pulse++) {
    for (int i_samp = 0; i_samp < wave.size(); i_samp++) {
      cpi_matrix(i_samp, i_pulse) = wave[i_samp];
    }
  }

  // Compute and plot the matched filter response
  auto autocorr = MatchedFilterResponse(wave, mf);
  figure();
  plot(db(abs(autocorr)));

  // Compute the range-doppler map and do CFAR
  auto rd_map = RangeDopplerMap(cpi_matrix, mf);
  Matrix2D<double> rd_map_db(rd_map.rows(), rd_map.cols(),
                             db(abs(rd_map.vector())));
  figure();
  image(rd_map_db, true);
  // rd_map_db = rd_map;

  show();
}