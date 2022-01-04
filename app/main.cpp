#include "eigen-config.h"
#include <matplot/matplot.h>

#include <Eigen/Dense>

#include "cfar.h"

#include "linearfmwaveform.h"
#include "rangedoppler.h"
using namespace plasma;
using namespace matplot;
using namespace Eigen;
int main() {
  // Generate the waveform and matched filter
  auto lfm = LinearFMWaveform(10e6, 10e-6, 10e3, 20e6);
  MatrixXcd wave =
      Map<MatrixXcd>(lfm.waveform().data(), lfm.waveform().size(), 1);
  VectorXcd mf =
      Map<VectorXcd>(lfm.MatchedFilter().data(), lfm.MatchedFilter().size());
  // Generate a fast-time slow-time matrix
  // TODO: Simulate this for targets with nonzero range and doppler
  auto num_pulses_cpi = 64;
  auto cpi_matrix = MatrixXcd(num_pulses_cpi, num_pulses_cpi);
  cpi_matrix.colwise() = Map<VectorXcd>(wave.data(), wave.size());

  MatrixXcd rd_map = RangeDopplerMap(cpi_matrix,mf);
  MatrixXd rd_map_db = 10*log10(abs(rd_map.array())).matrix();
  figure();
  auto ax = gca();
  auto x_min = -rd_map.cols()/2;
  auto x_max = rd_map.cols()/2;
  auto y_min = 0;
  auto y_max = rd_map.rows();
  ax->imagesc(x_min,x_max,y_min,y_max,rd_map_db.vector2d());
  ax->xlabel("(Centered) Pulse Index");
  ax->ylabel("Range Bin Index");

  colorbar();
  show();
  return 0;
}