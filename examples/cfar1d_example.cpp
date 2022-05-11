/**
 * Created on Tue Jan 04 2022
 *
 * Shane Flandermeyer, shaneflandermeyer@gmail.com
 *
 * A simple example usage of the CFAR detection object when the input is
 * gaussian noise with a time-varying variance. This example is adapted from
 * https://www.mathworks.com/help/phased/ug/constant-false-alarm-rate-cfar-detection.html
 */

#include "cfar1d.h"
#include "matrix_utils.h"

#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>

using namespace plasma;
using namespace matplot;
using namespace Eigen;
int main() {

  //! CFAR parameters
  auto method = "CA";
  size_t num_guard_cells = 2;
  size_t num_train_cells = 200;
  auto pfa = 1e-3;
  CFARDetector cfar{num_train_cells, num_guard_cells, pfa};

  //! Generate data
  // The input data is a square-law input signal with increasing noise power
  auto noise_power = pow(10, -10 / 10);
  size_t num_points = 10e3;
  // std::default_random_engine gen;
  MatrixXcd rsamp(num_points, 1);
  MatrixXd x(rsamp.rows(), rsamp.cols());
  // Start with samples from a complex standard normal distribution
  std::mt19937 gen{1000};
  std::normal_distribution<> normal{0, 1};
  for (size_t i = 0; i < num_points; ++i)
    rsamp(i) = std::complex<double>(normal(gen), normal(gen));
  // Create the square-law input signal
  ArrayXd ramp = ArrayXd::LinSpaced(num_points, 1, 10);
  x = abs2(sqrt(noise_power * ramp / 2) * rsamp.array()).matrix();
  // x = hcat(x,x);

  //! Write to a file
  // std::vector<double> filevec(x.data(), x.data() + x.size());
  // write_binary<double>("/home/shane/bin.dat",filevec);

  //! Do CFAR
  DetectionReport det = cfar.detect(x);

  //! Figures
  // Input data
  std::vector<double> xvec(x.data(), x.data() + x.size());
  std::vector<double> threshvec(det.threshold.data(),
                                det.threshold.data() + det.threshold.size());
  std::vector<size_t> indices(det.indices.col(0).data(),
                              det.indices.col(0).data() +
                                  det.indices.col(0).size());
  std::vector<double> detvec(det.indices.size());
  for (size_t i = 0; i < det.indices.size(); ++i)
    detvec[i] = x(det.indices(i));

  std::cout << "Number of Detections: " << det.num_detections << std::endl;

  plot(xvec);
  hold(true);
  plot(threshvec);
  plot(indices, detvec, "o");
  hold(false);
  show();
  return 0;
}