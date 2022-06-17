#include "filter.h"
#include <chrono>

using namespace std::chrono;
namespace plasma {
std::vector<std::complex<float>>
conv(const std::vector<std::complex<float>> &x1,
     const std::vector<std::complex<float>> &x2, int num_threads) {
  // Create copies of the input vectors, padded to the convolution size
  size_t nconv = x1.size() + x2.size() - 1;
  std::vector<std::complex<float>> x1_padded(nconv, 0), x2_padded(nconv, 0);
  memcpy(x1_padded.data(), x1.data(), x1.size() * sizeof(std::complex<float>));
  memcpy(x2_padded.data(), x2.data(), x2.size() * sizeof(std::complex<float>));

  // Convert the input vectors to the frequency domain
  FFT<std::complex<float>, true> fft(nconv, num_threads);
  fft.input(x1_padded.data());
  fft.execute();
  std::vector<std::complex<float>> f1(fft.output(), fft.output() + nconv);
  fft.input(x2_padded.data());
  fft.execute();
  std::vector<std::complex<float>> f2(fft.output(), fft.output() + nconv);
  // Element wise multiply
  std::vector<std::complex<float>> prod(nconv);
  for (size_t i = 0; i < nconv; i++) {
    prod[i] = f1[i] * f2[i];
  }
  // IFFT
  FFT<std::complex<float>, false> ifft(nconv, num_threads);
  ifft.input(prod.data());
  ifft.execute();

  return std::vector<std::complex<float>>(ifft.output(), ifft.output() + nconv);
}

Eigen::ArrayXXcf conv(const Eigen::ArrayXXcf &x, const Eigen::ArrayXcf &h,
                      int num_threads) {
  // Create copies of the inputs, padded to the convolution size
  size_t nconv = x.rows() + h.size() - 1;
  Eigen::ArrayXXcf x_padded = Eigen::ArrayXXcf::Zero(nconv, x.cols());
  Eigen::ArrayXcf h_padded = Eigen::ArrayXcf::Zero(nconv);
  x_padded.block(0, 0, x.rows(), x.cols()) = x;
  h_padded.segment(0, h.size()) = h;

  // Define the FFT objects to be used for all computations
  FFT<std::complex<float>, true> fft(nconv, num_threads);
  FFT<std::complex<float>, false> ifft(nconv, num_threads);
  Eigen::ArrayXXcf out(nconv, x.cols());
  Eigen::ArrayXcf X, H, prod;
  for (size_t i = 0; i < x.cols(); i++) {
    X = Eigen::Map<Eigen::ArrayXcf>(fft.execute(x_padded.col(i).data()), nconv);
    H = Eigen::Map<Eigen::ArrayXcf>(fft.execute(h_padded.data()), nconv);
    // Element wise multiply
    prod = X * H;

    // IFFT
    out.col(i) = Eigen::Map<Eigen::ArrayXcf>(ifft.execute(prod.data()), nconv);
  }
  return out;
}
} // namespace plasma
