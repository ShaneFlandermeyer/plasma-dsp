#include "cfar2d.h"

namespace plasma {

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

// DetectionReport CFARDetector2D::detect(const Eigen::MatrixXd &x, size_t cut_row,
//                                        size_t cut_col) {
//   DetectionReport result(x.block(cut_row,cut_col,1,1).matrix());
//   detect(x, cut_row, cut_col, result);
//   result.num_detections = result.detections.cast<int>().sum();

//   ComputeDetectionIndices(result);
//   return result;
// }

DetectionReport CFARDetector2D::detect(const Eigen::MatrixXd &x,
                                       const Eigen::Array2Xi &indices) {
  DetectionReport result(x);
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
  for (size_t i = 0; i < indices.rows(); ++i) {
    detect(x, indices(i, 0), indices(i, 1), result);
  }
  result.num_detections = result.detection.cast<int>().sum();

  ComputeDetectionIndices(result);
  return result;
}

DetectionReport CFARDetector2D::detect(const Eigen::MatrixXd &x) {
  DetectionReport result(x);
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
  for (size_t i = 0; i < x.rows(); ++i)
    for (size_t j = 0; j < x.cols(); ++j)
      detect(x, i, j, result);
  result.num_detections = result.detection.cast<int>().sum();

  ComputeDetectionIndices(result);
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
             num_guard_left + num_guard_right + 1) = 0;
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
  double power = (block * mask).sum();

  // Compute the threshold factor and the threshold itself
  double alpha = (pow(d_pfa, -1 / (double)num_train_bins) - 1);
  result.threshold(cut_row, cut_col) = alpha * power;
  // TODO: Account for closely-spaced detections that are probably the same
  result.detection(cut_row, cut_col) =
      x(cut_row, cut_col) > result.threshold(cut_row, cut_col);
}


}