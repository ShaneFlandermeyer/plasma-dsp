#include "fft.h"
#include <fftw3.h>

namespace plasma {
template <class T, bool forward> FFT<T, forward>::~FFT() {
  fftwf_destroy_plan((fftwf_plan)d_plan);
  fftwf_cleanup_threads();
}

template <bool forward> FFT<double, forward>::~FFT() {
  fftw_destroy_plan((fftw_plan)d_plan);
  fftw_cleanup_threads();
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

template <bool forward>
FFT<double, forward>::FFT(size_t fft_size, size_t num_threads)
    : d_size(fft_size), d_num_threads(num_threads), d_input(fft_size),
      d_output(fft_size) {
  // Initialize threads
  if (num_threads > 1) {
    fftw_init_threads();
    fftw_plan_with_nthreads(num_threads);
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

template <bool forward> void FFT<double, forward>::execute() {
  fftw_execute((fftw_plan)d_plan);
  if (not forward) {
    d_output /= d_size;
  }
}

template <class T, bool forward>
fft_output<T, forward>::type *
FFT<T, forward>::execute(typename fft_input<T, forward>::type *input) {
  memcpy(d_input.data(), input,
         sizeof(typename fft_input<T, forward>::type) * d_size);
  execute();
  return output();
}

template <bool forward>
fft_output<double, forward>::type *FFT<double, forward>::execute(
    typename fft_input<double, forward>::type *input) {
  memcpy(d_input.data(), input,
         sizeof(typename fft_input<double, forward>::type) * d_size);
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
void FFT<std::complex<double>, true>::initialize_plan(size_t fft_size) {
  d_plan = fftw_plan_dft_1d(fft_size,
                            reinterpret_cast<fftw_complex *>(d_input.data()),
                            reinterpret_cast<fftw_complex *>(d_output.data()),
                            FFTW_FORWARD, FFTW_MEASURE);
}

template <>
void FFT<std::complex<float>, false>::initialize_plan(size_t fft_size) {
  d_plan = fftwf_plan_dft_1d(fft_size,
                             reinterpret_cast<fftwf_complex *>(d_input.data()),
                             reinterpret_cast<fftwf_complex *>(d_output.data()),
                             FFTW_BACKWARD, FFTW_MEASURE);
}

template <>
void FFT<std::complex<double>, false>::initialize_plan(size_t fft_size) {
  d_plan = fftw_plan_dft_1d(fft_size,
                            reinterpret_cast<fftw_complex *>(d_input.data()),
                            reinterpret_cast<fftw_complex *>(d_output.data()),
                            FFTW_BACKWARD, FFTW_MEASURE);
}

template <> void FFT<float, true>::initialize_plan(size_t fft_size) {
  d_plan = fftwf_plan_dft_r2c_1d(
      fft_size, d_input.data(),
      reinterpret_cast<fftwf_complex *>(d_output.data()), FFTW_MEASURE);
}
template <> void FFT<double, true>::initialize_plan(size_t fft_size) {
  d_plan = fftw_plan_dft_r2c_1d(
      fft_size, d_input.data(),
      reinterpret_cast<fftw_complex *>(d_output.data()), FFTW_MEASURE);
}

template <> void FFT<float, false>::initialize_plan(size_t fft_size) {
  d_plan = fftwf_plan_dft_c2r_1d(
      fft_size, reinterpret_cast<fftwf_complex *>(d_input.data()),
      d_output.data(), FFTW_MEASURE);
}

template <> void FFT<double, false>::initialize_plan(size_t fft_size) {
  d_plan = fftw_plan_dft_c2r_1d(
      fft_size, reinterpret_cast<fftw_complex *>(d_input.data()),
      d_output.data(), FFTW_MEASURE);
}

template <>
FFT<double, true>::FFT(size_t fft_size, size_t num_threads)
    : d_size(fft_size), d_num_threads(num_threads), d_input(fft_size),
      d_output(fft_size) {
  // Initialize threads
  if (num_threads > 1) {
    fftw_init_threads();
    fftw_plan_with_nthreads(num_threads);
  }
  // Create plan
  initialize_plan(fft_size);
}

template <typename T, bool forward>
fft_output<T, forward>::type *FFT<T, forward>::output() {
  typename fft_output<T, forward>::type *out =
      new typename fft_output<T, forward>::type[d_size];
  memcpy(out, d_output.data(),
         sizeof(typename fft_output<T, forward>::type) * d_size);
  return d_output.data();
}

template <bool forward>
fft_output<double, forward>::type *FFT<double, forward>::output() {
  typename fft_output<double, forward>::type *out =
      new typename fft_output<double, forward>::type[d_size];
  memcpy(out, d_output.data(),
         sizeof(typename fft_output<double, forward>::type) * d_size);
  return d_output.data();
}

template class FFT<std::complex<float>, true>;
template class FFT<std::complex<float>, false>;
template class FFT<float, true>;
template class FFT<float, false>;

template class FFT<std::complex<double>, true>;
template class FFT<std::complex<double>, false>;
template class FFT<double, true>;
template class FFT<double, false>;

} // namespace plasma
