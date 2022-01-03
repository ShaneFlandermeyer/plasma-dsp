#include "cfar.h"

#include <iostream>

namespace plasma {

std::vector<bool> cfar(Eigen::MatrixXd &x, size_t cut_index) {
  using namespace Eigen;
  ArrayXd cut = x.row(cut_index - 1);

  // CFAR parameters
  // TODO: Make these function arguments
  auto method = "CA";
  auto num_guard_cells = 2;
  auto num_train_cells = 20;
  auto pfa = 1e-3;

  // Average power of the training cells
  size_t left_start_cell =
      (cut_index - 1) - num_guard_cells / 2 - num_train_cells / 2;
  ArrayXXd left =
      x.block(left_start_cell, 0, num_train_cells / 2, x.cols()).array();
  size_t right_start_cell = (cut_index - 1) + num_guard_cells / 2 + 1;
  ArrayXXd right =
      x.block(right_start_cell, 0, num_train_cells / 2, x.cols()).array();
  ArrayXd power = (left.array() + right.array()).colwise().sum();
  // Compute the threshold factor and the threshold
  size_t N = num_train_cells;
  auto alpha = (pow(pfa, -1 / (double)N) - 1);
  ArrayXd T = alpha * power;

  // Compare data to the threshold and return the results as a vector of bool
  Array<int, Dynamic, 1> detections = (cut > T).cast<int>();
  return std::vector<bool>(detections.data(),
                           detections.data() + detections.size());
}

} // namespace plasma
