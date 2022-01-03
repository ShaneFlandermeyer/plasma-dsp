#include "cfar.h"
#include "config.h"
#include "linearfmwaveform.h"
#include "matrix-utils.h"
#include "rangedoppler.h"
#include "vector-utils.h"

#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>

using namespace plasma;
using namespace matplot;
using namespace Eigen;
int main() {

  //! CFAR parameters
  auto method = "CA";
  auto num_guard_cells = 2;
  auto num_train_cells = 20;
  auto pfa = 1e-3;

  //! Generate data
  // The data sequence is 23 samples long, and the CUT is at index 12. This
  // leaves 10 training cells and 1 guard cell on each side of the CUT.
  // The false alarm rate is calculated using 100k Monte carlo trials
  // TODO: Create seed
  auto noise_power = pow(10, -10 / 10);
  size_t num_trials = 100e3;
  size_t num_cells = 23;
  size_t cut_index = 12;
  // Compute the input samples
  // std::default_random_engine gen;
  std::mt19937 gen{1000};
  std::normal_distribution<> normal{0, 1};
  MatrixX<std::complex<double>> rsamp(num_cells, num_trials);
  MatrixX<double> x(num_cells, num_trials);
  // num_cells x num_trials matrix of AWGN samples
  for (size_t i = 0; i < num_cells; ++i)
    for (size_t j = 0; j < num_trials; ++j)
      rsamp(i, j) = std::complex<double>(normal(gen), normal(gen));
  // Noise samples after the square law detector
  x = abs2(sqrt(noise_power / 2) * rsamp.array());

  // TODO: Delete this
  std::vector<double> outvec(x.data(),x.data() + x.size());
  write_binary<double>("/home/shane/bin.dat",outvec);

  //! Do CFAR
  std::vector<bool> x_detected = cfar(x, cut_index);
  //! Figures
  // figure();
  // std::vector<double> x2 = x.vector1d();
  // plot(x2);
  // show();
  return 0;
}