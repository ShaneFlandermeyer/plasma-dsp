#include "filter.h"
namespace plasma {

size_t nextpow2(size_t n) {
  size_t m = 1;
  while (m < n) {
    m *= 2;
  }
  return m;
}

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
  nconv = nextpow2(nconv);
  Eigen::ArrayXXcf x_padded = Eigen::ArrayXXcf::Zero(nconv, x.cols());
  Eigen::ArrayXcf h_padded = Eigen::ArrayXcf::Zero(nconv);
  x_padded.block(0, 0, x.rows(), x.cols()) = x;
  h_padded.segment(0, h.size()) = h;

  // Define the FFT objects to be used for all computations
  FFT<std::complex<float>, true> fft(nconv, num_threads);
  FFT<std::complex<float>, false> ifft(nconv, num_threads);
  Eigen::ArrayXXcf out(x.rows() + h.size() - 1, x.cols());
  Eigen::ArrayXcf X, H, prod;
  for (size_t i = 0; i < x.cols(); i++) {
    X = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
        fft.execute(x_padded.col(i).data()), nconv);
    H = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
        fft.execute(h_padded.data()), nconv);
    // Element wise multiply
    prod = X * H;

    // IFFT
    out.col(i) = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
        ifft.execute(prod.data()), x.rows() + h.size() - 1);
  }
  return out;
}

Eigen::ArrayXd filter(const Eigen::ArrayXd &h, const Eigen::ArrayXd &x,
                      int num_threads) {
  // Create copies of the inputs, padded to the convolution size
  size_t nconv = x.size() + h.size() - 1;
  nconv = nextpow2(nconv);
  Eigen::ArrayXf x_padded = Eigen::ArrayXf::Zero(nconv);
  Eigen::ArrayXf h_padded = Eigen::ArrayXf::Zero(nconv);
  x_padded(Eigen::seqN(0, x.size())) = x.cast<float>();
  h_padded(Eigen::seqN(0, h.size())) = h.cast<float>();

  // Define the FFT objects to be used for all computations
  FFT<float, true> fft(nconv, num_threads);
  FFT<float, false> ifft(nconv, num_threads);
  Eigen::ArrayXf out(nconv);
  Eigen::ArrayXcf X = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
      fft.execute(x_padded.data()), nconv);
  Eigen::ArrayXcf H = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
      fft.execute(h_padded.data()), nconv);
  // Element wise multiply
  Eigen::ArrayXcf prod = X * H;

  // IFFT
  out = Eigen::Map<Eigen::ArrayXf, Eigen::Aligned>(ifft.execute(prod.data()),
                                                    x.size());
  return out.cast<double>();
  // FFT<float, true> fft(in.size(), num_threads);
  // FFT<float, false> ifft(in.size(), num_threads);

  // Eigen::ArrayXf pad_filter = Eigen::ArrayXf::Zero(in.size());
  // size_t filter_size = std::min(in.size(), filter.size());
  // pad_filter.head(filter_size) = filter.head(filter_size).cast<float>();
  // Eigen::ArrayXf in_float = in.cast<float>();

  // Eigen::ArrayXcf filter_fft = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
  //     fft.execute(pad_filter.data()), filter_size);
  // Eigen::ArrayXcf in_fft = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
  //     fft.execute(in_float.data()), filter_size);
  // Eigen::ArrayXcf prod = in_fft * filter_fft;
  // Eigen::ArrayXf out = Eigen::Map<Eigen::ArrayXf, Eigen::Aligned>(
  //     ifft.execute(prod.data()), filter_size);
  // return out.cast<double>();
}
} // namespace plasma
