#include "filter.h"

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
} // namespace plasma
