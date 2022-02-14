#include "linear_fm_waveform.h"
#include "pulse_doppler.h"
#include <matplot/matplot.h>

using namespace matplot;
using namespace plasma;
using namespace Eigen;

int main() {
  // Waveform parameter
  double B = 50e6;
  double fs = 4 * B;
  double Tp = 5e-6;
  double prf = 20e3;
  LinearFMWaveform wave(B, Tp, prf, fs);
  VectorXcd x = wave.waveform();

  // Target parameters
  double range = 1e3;
  double tau = 2 * range / physconst::c;

  VectorXcd y; // = delay(x,5e-6,(size_t)(fs/prf),fs);
  VectorXcd h = wave.MatchedFilter();
  size_t num_samps_pri = (int)(fs / prf);
  size_t num_range_bins = num_samps_pri + h.size() - 1;
  size_t num_pulses = 32;
  MatrixXcd fast_time_slow_time = MatrixXcd::Zero(num_samps_pri, num_pulses);
  MatrixXcd range_pulse_map = MatrixXcd::Zero(num_range_bins, num_pulses);
  MatrixXcd range_doppler_map = MatrixXcd::Zero(num_range_bins, num_pulses);
  for (size_t m = 0; m < num_pulses; m++) {
    y = delay(x, tau, num_samps_pri, fs);
    // TODO: Add a scale factor
    fast_time_slow_time.col(m) = y;
    range_pulse_map.col(m) = conv(y, h);
  }

  // Range doppler map
  // TODO: Make a function for matrix FFTs
  Eigen::FFT<double> fft;
  Eigen::VectorXcd tmp;
  for (size_t i = 0; i < range_doppler_map.rows(); i++) {
    fft.fwd(tmp, range_pulse_map.row(i));
    fftshift(tmp.data(),tmp.size());
    range_doppler_map.row(i) = tmp;
  }

  // Convert the Eigen matrix to a vector of vectors
  figure();
  std::vector<std::vector<double>> xv(
      range_doppler_map.rows(), std::vector<double>(range_doppler_map.cols()));
  for (size_t i = 0; i < xv.size(); i++) {
    for (size_t j = 0; j < xv.front().size(); j++) {
      xv[i][j] = abs(range_doppler_map(i, j));
    }
  }
  imagesc(xv);

  show();

  return 0;
}