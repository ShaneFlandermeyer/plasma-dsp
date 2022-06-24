#include "fft.h"
#include <fftw3.h>

namespace plasma {
template <class T, bool forward> FFT<T, forward>::~FFT() {
  fftwf_destroy_plan((fftwf_plan)d_plan);
  fftwf_cleanup_threads();
}


template <class T, bool forward>
FFT<T, forward>::FFT(size_t fft_size, size_t num_threads)
    : d_size(fft_size), d_num_threads(num_threads), d_input(fft_size),
      d_output(fft_size) {
  // Initialize threads
  if (num_threads > 1) {
    fftwf_init_threads();
    fftwf_plan_with_nthreads(num_threads);
  }
  // Create plan
  initialize_plan(fft_size);
}


template <class T, bool forward> void FFT<T, forward>::execute() {
  fftwf_execute((fftwf_plan)d_plan);
  if (not forward) {
    d_output /= d_size;
  }
}


template <class T, bool forward>
typename fft_output<T, forward>::type *
FFT<T, forward>::execute(typename fft_input<T, forward>::type *input) {
  memcpy(d_input.data(), input,
         sizeof(typename fft_input<T, forward>::type) * d_size);
  execute();
  return output();
}

template <>
void FFT<std::complex<float>, true>::initialize_plan(size_t fft_size) {
  d_plan = fftwf_plan_dft_1d(fft_size,
                             reinterpret_cast<fftwf_complex *>(d_input.data()),
                             reinterpret_cast<fftwf_complex *>(d_output.data()),
                             FFTW_FORWARD, FFTW_MEASURE);
}

template <>
void FFT<std::complex<float>, false>::initialize_plan(size_t fft_size) {
  d_plan = fftwf_plan_dft_1d(fft_size,
                             reinterpret_cast<fftwf_complex *>(d_input.data()),
                             reinterpret_cast<fftwf_complex *>(d_output.data()),
                             FFTW_BACKWARD, FFTW_MEASURE);
}

template <> void FFT<float, true>::initialize_plan(size_t fft_size) {
  d_plan = fftwf_plan_dft_r2c_1d(
      fft_size, d_input.data(),
      reinterpret_cast<fftwf_complex *>(d_output.data()), FFTW_MEASURE);
}


template <> void FFT<float, false>::initialize_plan(size_t fft_size) {
  d_plan = fftwf_plan_dft_c2r_1d(
      fft_size, reinterpret_cast<fftwf_complex *>(d_input.data()),
      d_output.data(), FFTW_MEASURE);
}

template <typename T, bool forward>
typename fft_output<T, forward>::type *FFT<T, forward>::output() {
  typename fft_output<T, forward>::type *out =
      new typename fft_output<T, forward>::type[d_size];
  memcpy(out, d_output.data(),
         sizeof(typename fft_output<T, forward>::type) * d_size);
  return d_output.data();
}

template class FFT<std::complex<float>, true>;
template class FFT<std::complex<float>, false>;
template class FFT<float, true>;
template class FFT<float, false>;


} // namespace plasma
