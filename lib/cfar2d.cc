#include "cfar2d.h"
#include <arrayfire.h>

namespace plasma {

CFARDetector2D::CFARDetector2D(size_t size_guard, size_t size_train,
                               float pfa) {
  d_guard_win_size[0] = size_guard;
  d_guard_win_size[1] = size_guard;

  d_train_win_size[0] = size_train;
  d_train_win_size[1] = size_train;

  d_pfa = pfa;
}

CFARDetector2D::CFARDetector2D(int *guard_size, int *train_size, float pfa){
  d_guard_win_size[0] = guard_size[0];
  d_guard_win_size[1] = guard_size[1];

  d_train_win_size[0] = train_size[0];
  d_train_win_size[1] = train_size[1];

  d_pfa = pfa;
}

// ArrayFire
af::array CFARDetector2D::detect(const af::array &x) {

  //Setting up the range size for the cfar_temp
  size_t winR1 = 1 - d_guard_win_size[0] - d_train_win_size[0];
  size_t winR2 = 1 + d_guard_win_size[0] + d_train_win_size[0];

  size_t LR = winR2 - winR1 + 1;

  //Setting up the doppler size for the cfar_temp
  size_t winD1 = 1 - d_guard_win_size[1] - d_train_win_size[1];
  size_t winD2 = 1 + d_guard_win_size[1] + d_train_win_size[1];
  
  size_t LD = winD2 - winD1 + 1;

  //creating the cfar_temp
  af::array cfar_temp = af::constant(1, LR, LD);
  cfar_temp(af::seq(d_train_win_size[0], cfar_temp.dims(0) - d_train_win_size[0] - 1), af::seq(d_train_win_size[1], cfar_temp.dims(1) - d_train_win_size[1] - 1)) = 0;
  size_t num_train_bins = af::sum<int>(cfar_temp);
  cfar_temp = cfar_temp / (af::sum<float>(cfar_temp));

  //Creating the noise power array
  af::array power =af::ifft2(af::fft2(cfar_temp, x.dims(0), x.dims(1)) * af::fft2(x));

  //Calculating alpha
  float alpha = num_train_bins * (pow(d_pfa, -1 / (double)num_train_bins) - 1);

  //Creating a bool array where the detetions are.
  af::array detections = (x > power * alpha);

  return detections;
}

} // namespace plasma