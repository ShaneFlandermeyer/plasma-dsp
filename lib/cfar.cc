#include "cfar.h"

#include <iostream>

namespace plasma {

CFARDetector::CFARDetector(size_t num_train, size_t num_guard, double pfa) {
  d_num_guard_cells = num_guard;
  d_num_train_cells = num_train;
  d_pfa = pfa;
}

std::vector<bool> CFARDetector::detect(const Eigen::MatrixXd &x) {
  // TODO: Implement this - should probably return Eigen vectors/matrices
  std::vector<bool> detections(x.size(), false);
  // for (size_t i = 0; i < x.rows(); ++i) {
  //     detections.push_back(detect(x, i));
  // }
  return detections;
}

std::vector<bool> CFARDetector::detect(const Eigen::MatrixXd &x,
                                       size_t cut_index) {
  using namespace Eigen;
  ArrayXd cut = x.row(cut_index - 1);

  // Index of the beginning and
  int start_cell_front =
      std::max(static_cast<int>((cut_index - 1) - d_num_guard_cells / 2 -
                                d_num_train_cells / 2),
               0);
  int end_cell_front =
      std::max(static_cast<int>((cut_index - 1) - d_num_guard_cells / 2), 0);

  int start_cell_rear =
      std::min(static_cast<int>((cut_index - 1) + d_num_guard_cells / 2 + 1),
               static_cast<int>(x.rows()));
  int end_cell_rear =
      std::min(static_cast<int>(start_cell_rear + d_num_train_cells / 2),
               static_cast<int>(x.rows()));
  int num_train_cells_front = end_cell_front - start_cell_front;
  int num_train_cells_rear = end_cell_rear - start_cell_rear;
  if (num_train_cells_front < num_train_cells_rear) {
    num_train_cells_rear += d_num_train_cells / 2 - num_train_cells_front;
  } else {
    num_train_cells_front += d_num_train_cells / 2 - num_train_cells_rear;
    start_cell_front = end_cell_front - num_train_cells_front;
  }
  // Average power of the training cells
  // FIXME: Properly zero pad this so the power can be calculated
  ArrayXXd front =
      x.block(start_cell_front, 0, num_train_cells_front, x.cols()).array();
  ArrayXXd rear =
      x.block(start_cell_rear, 0, num_train_cells_rear, x.cols()).array();
  ArrayXd power = (front.array() + rear.array()).colwise().sum();
  // Compute the threshold factor and the threshold
  size_t N = d_num_train_cells;
  auto alpha = (pow(d_pfa, -1 / (double)N) - 1);
  ArrayXd T = alpha * power;

  // Compare data to the threshold and return the results as a vector of bool
  Array<int, Dynamic, 1> detections = (cut > T).cast<int>();
  return std::vector<bool>(detections.data(),
                           detections.data() + detections.size());
}

} // namespace plasma
