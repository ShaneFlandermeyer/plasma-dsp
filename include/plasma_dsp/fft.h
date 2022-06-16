#ifndef EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4
#define EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4

#include <complex>
#include <iostream>
#include <Eigen/Dense>

namespace plasma {

template <class T> class FFT {
private:
  size_t d_num_threads;
  size_t d_size;
  Eigen::ArrayX<T> d_input;
  Eigen::ArrayX<T> d_output;
  void *d_plan;

public:
  FFT(size_t fft_size, size_t num_threads = 1);
  ~FFT();
  void execute();

  T *input() { return d_input.data(); }
  T *output() { return d_output.data(); }
};

} // namespace plasma

#endif /* EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4 */
