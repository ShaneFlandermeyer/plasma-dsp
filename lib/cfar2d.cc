#include "cfar2d.h"
#include "detector.h"
#include <iostream>
#include <arrayfire.h>

namespace plasma {

CFARDetector2D::CFARDetector2D(size_t guard_win_size, size_t train_win_size,
                               double pfa) {
  d_guard_win_size = {guard_win_size, guard_win_size};
  d_train_win_size = {train_win_size, train_win_size};
  d_pfa = pfa;
}

CFARDetector2D::CFARDetector2D(const std::array<size_t, 2> &guard_win_size,
                               const std::array<size_t, 2> &train_win_size,
                               double pfa) {
  d_guard_win_size = guard_win_size;
  d_train_win_size = train_win_size;
  d_pfa = pfa;
}

DetectionReport CFARDetector2D::detect(const af::array &x) {

  // Compute the window size (cell under test + number of train/guard bins on
  // either side in each dimension).
  int num_win_rows = 2 * (d_train_win_size[0] + d_guard_win_size[0]) + 1;
  int num_win_cols = 2 * (d_train_win_size[1] + d_guard_win_size[1]) + 1;

  // Create the CFAR mask, where the training bins have value 1/N and guard bins
  // and CUT are 0.
  af::array window = af::constant(1, num_win_rows, num_win_cols, f32);
  window(af::seq(d_train_win_size[0], num_win_rows - d_train_win_size[0] - 1),
         af::seq(d_train_win_size[1], num_win_cols - d_train_win_size[1] - 1)) =
      0;
  int num_train_bin = window.nonzeros();
  window /= num_train_bin;

  // Convolve the CFAR mask with the input array via an FFT
  af::array local_mean =
      af::ifft2(af::fft2(window, x.dims(0), x.dims(1)) * af::fft2(x));

  // Make a decision for each CUT
  double alpha = num_train_bin * (pow(d_pfa, -1 / (double)num_train_bin) - 1);
  af::array detections = (x > alpha * local_mean);

  // Creating a DetectionReport with the detections then computing the indices.
  DetectionReport results(detections);

  return results;
}

} // namespace plasma