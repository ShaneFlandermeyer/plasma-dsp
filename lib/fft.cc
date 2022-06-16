#include "fft.h"
#include <fftw3.h>

namespace plasma {
template <class T> FFT<T>::~FFT() {
  fftwf_destroy_plan((fftwf_plan)d_plan);
  fftw_cleanup_threads();
}

template <class T>
FFT<T>::FFT(size_t fft_size, size_t num_threads)
    : d_size(fft_size), d_num_threads(num_threads), d_input(fft_size),
      d_output(fft_size) {
  // Handle threads
  if (num_threads > 1) {
    fftwf_init_threads();
    fftwf_plan_with_nthreads(num_threads);
  }

  // Create the plan
  d_plan = fftwf_plan_dft_1d(fft_size,
                             reinterpret_cast<fftwf_complex *>(d_input.data()),
                             reinterpret_cast<fftwf_complex *>(d_output.data()),
                             FFTW_FORWARD, FFTW_MEASURE);
}

template <class T> void FFT<T>::execute() { fftwf_execute((fftwf_plan)d_plan); 
}

template class FFT<std::complex<float>>;
template class FFT<float>;

} // namespace plasma
