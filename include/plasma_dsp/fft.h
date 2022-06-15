#ifndef EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4
#define EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4

#include <complex>
#include <iostream>

namespace plasma {

template <class T> class FFT {
private:
  int d_num_threads;
  void *d_plan;

public:
  FFT();
  FFT(size_t fft_size, size_t num_threads = 1);
  ~FFT();
  void execute();
};

} // namespace plasma

#endif /* EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4 */
