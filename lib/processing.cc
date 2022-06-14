#include "processing.h"

namespace plasma {

size_t nextpow2(size_t n) {
  size_t p = 1;
  while (p < n)
    p *= 2;
  return p;
}

std::complex<float> *fft(std::complex<float> *in, int N, size_t num_threads) {
  fftwf_complex *out = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * N);
  fftwf_init_threads();
  fftwf_plan_with_nthreads(num_threads);
  fftwf_plan p = fftwf_plan_dft_1d(N, reinterpret_cast<fftwf_complex *>(in),
                                   out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftwf_execute(p);
  fftwf_destroy_plan(p);
  fftwf_cleanup_threads();
  return reinterpret_cast<std::complex<float> *>(out);
}

std::complex<double> *fft(std::complex<double> *in, int N, size_t num_threads) {
  fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
  fftw_init_threads();
  fftw_plan_with_nthreads(num_threads);
  fftw_plan p = fftw_plan_dft_1d(N, reinterpret_cast<fftw_complex *>(in), out,
                                 FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  fftw_cleanup_threads();
  return reinterpret_cast<std::complex<double> *>(out);
}

std::vector<std::complex<float>> fft(std::vector<std::complex<float>> &in,
                                     int N, size_t num_threads) {
  std::complex<float> *out = fft(in.data(), N, num_threads);
  return std::vector<std::complex<float>>(out, out + N);
}

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in,
                                      int N, size_t num_threads) {
  if (N == -1)
    N = in.size();

  fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
  fftw_init_threads();
  fftw_plan_with_nthreads(num_threads);
  fftw_plan p = fftw_plan_dft_1d(N, reinterpret_cast<fftw_complex *>(in.data()),
                                 out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  fftw_cleanup_threads();

  return std::vector<std::complex<double>>(
      reinterpret_cast<std::complex<double> *>(out),
      reinterpret_cast<std::complex<double> *>(out) + N);
}

// Eigen::ArrayXcf fft(Eigen::ArrayXcf &in, int N, size_t num_threads) {
//   if (N == -1)
//     N = in.size();
//   fftwf_complex *out = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) *
//   N); fftwf_init_threads(); fftwf_plan_with_nthreads(num_threads); fftwf_plan
//   p =
//       fftwf_plan_dft_1d(N, reinterpret_cast<fftwf_complex *>(in.data()),
//                         reinterpret_cast<fftwf_complex *>(in.data()),
//                         FFTW_FORWARD, FFTW_ESTIMATE);
//   fftwf_execute(p);

//   fftwf_destroy_plan(p);
//   fftwf_cleanup_threads();
//   return Eigen::Map<Eigen::ArrayXcf, Eigen::>(
//       reinterpret_cast<std::complex<float> *>(out), N);
// }

template <>
std::vector<double> ifft<double>(std::vector<std::complex<double>> in, int N) {
  // Create output vector
  if (N == -1)
    N = in.size();
  in.resize(N);
  auto out = std::vector<double>(N);
  // Create plan and compute IFFT
  fftw_plan p = fftw_plan_dft_c2r_1d(
      N, reinterpret_cast<fftw_complex *>(in.data()),
      reinterpret_cast<double *>(out.data()), FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  for (auto &x : out)
    x *= N;
  return out;
}

template <>
std::vector<std::complex<double>>
ifft<std::complex<double>>(std::vector<std::complex<double>> in, int N) {
  if (N == -1)
    N = in.size();
  in.resize(N);
  auto out = std::vector<std::complex<double>>(N);
  fftw_plan p = fftw_plan_dft_1d(N, reinterpret_cast<fftw_complex *>(in.data()),
                                 reinterpret_cast<fftw_complex *>(out.data()),
                                 FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  for (auto &x : out)
    x *= N;
  return out;
}

template <>
std::vector<float> ifft<float>(std::vector<std::complex<float>> in, int N) {
  // Create output vector
  if (N == -1)
    N = in.size();
  in.resize(N);
  auto out = std::vector<float>(N);
  // Create plan and compute IFFT
  fftwf_plan p = fftwf_plan_dft_c2r_1d(
      N, reinterpret_cast<fftwf_complex *>(in.data()),
      reinterpret_cast<float *>(out.data()), FFTW_ESTIMATE);
  fftwf_execute(p);
  fftwf_destroy_plan(p);
  for (auto &x : out)
    x *= N;
  return out;
}

template <>
std::vector<std::complex<float>>
ifft<std::complex<float>>(std::vector<std::complex<float>> in, int N) {
  if (N == -1)
    N = in.size();
  in.resize(N);
  auto out = std::vector<std::complex<float>>(N);
  fftwf_plan p =
      fftwf_plan_dft_1d(N, reinterpret_cast<fftwf_complex *>(in.data()),
                        reinterpret_cast<fftwf_complex *>(out.data()),
                        FFTW_BACKWARD, FFTW_ESTIMATE);
  fftwf_execute(p);
  fftwf_destroy_plan(p);
  for (auto &x : out)
    x *= N;
  return out;
}

} // namespace plasma
