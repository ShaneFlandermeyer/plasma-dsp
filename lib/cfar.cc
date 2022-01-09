#include "cfar.h"

namespace plasma {

// *****************************************************************************
// * CFARDetector
// *****************************************************************************
CFARDetector::CFARDetector(size_t num_train, size_t num_guard, double pfa) {
  d_num_guard_cells = num_guard;
  d_num_train_cells = num_train;
  d_pfa = pfa;
}

DetectionReport CFARDetector::detect(const Eigen::MatrixXd &x) {
  DetectionReport result;
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
  // TODO: Can the detection indices be computed and stored outside of the loop
  for (size_t i = 0; i < x.rows(); ++i) {
    detect(x, i, result);
  }
  // Store all the detection indices
  result.indices =
      Eigen::Array<size_t, Eigen::Dynamic, 2>(result.num_detections, 2);
  size_t i_detection = 0;
  for (size_t i = 0; i < x.rows(); ++i) {
    for (size_t j = 0; j < x.cols(); ++j) {
      if (result.detections(i, j)) {
        result.indices.row(i_detection) << i, j;
      }
    }
  }
  return result;
}

// TODO: Consider making this private
void CFARDetector::detect(const Eigen::MatrixXd &x, size_t cut_index,
                          DetectionReport &result) {
  using namespace Eigen;
  // Current cell under test
  ArrayXXd cut = x.row(cut_index);

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
  ArrayXXd power = (front.array() + rear.array()).colwise().sum();

  // Compute the threshold factor and the threshold
  double alpha = (pow(d_pfa, -1 / (double)d_num_train_cells) - 1);
  ArrayXXd threshold = alpha * power;

  // Compare data to the threshold
  Array<bool, Dynamic, Dynamic> detections = cut > threshold;
  // Initialize the result struct if it hasn't been done yet
  if (result.detections.size() == 0)
    result.detections.resize(x.rows(), x.cols());
  if (result.threshold.size() == 0)
    result.threshold.resize(x.rows(), x.cols());
  for (size_t i = 0; i < cut.size(); ++i) {
    if (detections(i)) {
      result.num_detections++;
      // result.indices.conservativeResize(result.num_detections, 2);
      // result.indices.row(result.num_detections - 1) << cut_index, i;
      // result.indices.bottomRows(1) << cut_index, i;
    }
  }

  result.detections.row(cut_index) = detections;
  result.threshold.row(cut_index) = threshold;
}

// *****************************************************************************
// * CFARDetector2D
// *****************************************************************************
CFARDetector2D::CFARDetector2D(size_t size_guard, size_t size_train,
                               double pfa) {
  d_guard_win_size = size_guard;
  d_train_win_size = size_train;
  d_pfa = pfa;
}

CFARDetector2D::CFARDetector2D(Eigen::Array<size_t, 2, 1> size_guard,
                               Eigen::Array<size_t, 2, 1> size_train,
                               double pfa) {
  d_guard_win_size = size_guard;
  d_train_win_size = size_train;
  d_pfa = pfa;
}

DetectionReport CFARDetector2D::detect(const Eigen::MatrixXd &x) {
  DetectionReport result;
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
  for (size_t i = 0; i < x.rows(); ++i) {
    for (size_t j = 0; j < x.cols(); ++j) {
      detect(x, i, j, result);
    }
  }
  return result;
}

DetectionReport CFARDetector2D::detect(const Eigen::MatrixXd &x,
                                       const Eigen::Array2Xi &indices) {
  DetectionReport result;
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
  for (size_t i = 0; i < indices.rows(); ++i) {
    detect(x, indices(i, 0), indices(i, 1), result);
  }
  return result;
}

void CFARDetector2D::detect(const Eigen::MatrixXd &x, size_t cut_row,
                            size_t cut_col, DetectionReport &result) {
  using namespace Eigen;
  // Create the CFAR mask. This mask is a boolean matrix where an index of 1
  // indicates a training cell and an index of 0 indicates a guard cell or the
  // CUT.

  // First, determine the number of guard cells "available" in each
  // direction. This makes it possible to properly set the zero portion of the
  // mask
  size_t num_guard_left = std::min(cut_col, d_guard_win_size(1));
  size_t num_guard_right =
      std::min(x.cols() - 1 - cut_col, d_guard_win_size(1));
  size_t num_guard_up = std::min(cut_row, d_guard_win_size(0));
  size_t num_guard_down = std::min(x.rows() - 1 - cut_row, d_guard_win_size(0));
  // Do the same for the number of training cells. Note that for corner cases
  // the window may become asymmetric - the number of training cells will be
  // conserved but the number of guard cells may not, leading to a different
  // mask size than desired
  size_t num_train_left =
      std::min(cut_col - num_guard_left, d_train_win_size(1));
  size_t num_train_right = 2 * d_train_win_size(1) - num_train_left;
  size_t num_train_up = std::min(cut_row - num_guard_up, d_train_win_size(0));
  size_t num_train_down = 2 * d_train_win_size(0) - num_train_up;

  // The CUT index within the mask follows directly from above
  size_t mask_width =
      num_guard_left + num_guard_right + num_train_left + num_train_right + 1;
  size_t mask_height =
      num_guard_up + num_guard_down + num_train_up + num_train_down + 1;
  ArrayXXd mask = ArrayXXd::Ones(mask_height, mask_width);
  mask.block(num_train_up, num_train_left, num_guard_up + num_guard_down + 1,
             num_guard_left + num_guard_right + 1)
      .setZero();
  // The number of training bins in the mask is equal to the number of ones.
  // Guard bins (and the CUT) make up the rest of the mask
  size_t num_train_bins = mask.sum();
  size_t num_guard_bins = mask.size() - num_train_bins;

  // Apply the mask to the data and estimate the power using the sample mean of
  // the training cells
  size_t block_start_row = std::max(static_cast<int>(cut_row - mask_height), 0);
  size_t block_start_col = std::max(static_cast<int>(cut_col - mask_width), 0);
  ArrayXXd block =
      x.block(block_start_row, block_start_col, mask_height, mask_width);
  double power = (block * mask).sum() / num_train_bins;

  // Compute the threshold factor and the threshold itself
  double alpha = num_train_bins * (pow(d_pfa, -1 / (double)num_train_bins) - 1);
  double threshold = alpha * power;

  // Update results struct
  // TODO: Account for closely-spaced detections that are probably the same
  bool detection = x(cut_row, cut_col) > threshold;
  if (result.detections.size() == 0)
    result.detections.resize(x.rows(), x.cols());
  if (result.threshold.size() == 0)
    result.threshold.resize(x.rows(), x.cols());
  if (detection) {
    // Save the matrix indices of the new detections. Since we usually don't
    // know how many detections there will be a priori, we need to resize the
    // vector every time there's a new detection
    result.num_detections++;
    result.indices.conservativeResize(result.num_detections, 2);
    result.indices.bottomRows(1) << cut_row, cut_col;
  }
  result.detections(cut_row, cut_col) = detection;
  result.threshold(cut_row, cut_col) = threshold;
}

} // namespace plasma
