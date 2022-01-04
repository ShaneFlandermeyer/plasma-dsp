#include "cfar.h"

#include <iostream>

namespace plasma {

CFARDetector::CFARDetector(size_t num_train, size_t num_guard, double pfa) {
  d_num_guard_cells = num_guard;
  d_num_train_cells = num_train;
  d_pfa = pfa;
}

DetectionReport CFARDetector::detect(const Eigen::MatrixXd &x) {
  std::vector<bool> detections(x.rows(), false);
  DetectionReport result;
  for (size_t i = 0; i < x.rows(); ++i) {
    detect(x, i, result);
  }
  return result;
}

void CFARDetector::detect(const Eigen::MatrixXd &x, size_t cut_index,
                          DetectionReport &result) {
  using namespace Eigen;
  // Current cell under test
  ArrayXd cut = x.row(cut_index);

  // Index of the beginning and end of each window
  size_t front_win_start =
      std::max(static_cast<int>(cut_index - d_num_guard_cells / 2 -
                                d_num_train_cells / 2),
               0);
  size_t front_win_end =
      std::max(static_cast<int>(cut_index - d_num_guard_cells / 2), 0);

  size_t rear_win_start =
      std::min(static_cast<int>(cut_index + d_num_guard_cells / 2 + 1),
               static_cast<int>(x.rows()));
  size_t rear_win_end =
      std::min(static_cast<int>(rear_win_start + d_num_train_cells / 2),
               static_cast<int>(x.rows()));

  // Number of cells in each training window before compensation
  size_t num_train_cells_front = front_win_end - front_win_start;
  size_t num_train_cells_rear = rear_win_end - rear_win_start;
  // Resize the windows to use the desired number of training cells
  if (num_train_cells_front < num_train_cells_rear) {
    num_train_cells_rear += d_num_train_cells / 2 - num_train_cells_front;
  } else {
    num_train_cells_front += d_num_train_cells / 2 - num_train_cells_rear;
    front_win_start = front_win_end - num_train_cells_front;
  }

  // Compute the average power of the training cells
  // Since we perform element-wise addition here, we need to zero pad the
  // smaller window to the same size as the larger window
  size_t array_size = std::max(num_train_cells_front, num_train_cells_rear);
  ArrayXXd front(array_size, x.cols());
  ArrayXXd rear(array_size, x.cols());
  front.block(0, 0, num_train_cells_front, x.cols()) =
      x.block(front_win_start, 0, num_train_cells_front, x.cols());
  rear.block(0, 0, num_train_cells_rear, x.cols()) =
      x.block(rear_win_start, 0, num_train_cells_rear, x.cols());
  ArrayXd power = (front.array() + rear.array()).colwise().sum();

  // Compute the threshold factor and the threshold
  auto alpha = (pow(d_pfa, -1 / (double)d_num_train_cells) - 1);
  ArrayXd threshold = alpha * power;

  // Compare data to the threshold
  Array<int, Dynamic, 1> detections = (cut > threshold).cast<int>();

  // Update the results struct
  result.detections.push_back(detections(0));
  result.threshold.push_back(threshold(0));
  if (detections(0)) {
    result.indices.push_back(cut_index);
  }
}

} // namespace plasma
