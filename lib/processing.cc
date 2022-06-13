#include "processing.h"

namespace plasma {

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in,
                                      int N) {
  if (N == -1)
    N = in.size();
  in.resize(N);
  auto out = std::vector<std::complex<double>>(N);
  fftw_plan p = fftw_plan_dft_1d(N, reinterpret_cast<fftw_complex *>(in.data()),
                                 reinterpret_cast<fftw_complex *>(out.data()),
                                 FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  for (auto &x : out)
    x /= N;
  return out;
}

std::vector<std::complex<float>> fft(std::vector<std::complex<float>> &in,
                                     int N) {
  if (N == -1)
    N = in.size();
  in.resize(N);
  auto out = std::vector<std::complex<float>>(N);
  fftwf_plan p =
      fftwf_plan_dft_1d(N, reinterpret_cast<fftwf_complex *>(in.data()),
                        reinterpret_cast<fftwf_complex *>(out.data()),
                        FFTW_FORWARD, FFTW_ESTIMATE);
  fftwf_execute(p);
  fftwf_destroy_plan(p);
  for (auto &x : out)
    x /= N;
  return out;
}

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
