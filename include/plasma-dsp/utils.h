#ifndef B5F351BB_C14A_43DF_A96F_0159BAC8AD27
#define B5F351BB_C14A_43DF_A96F_0159BAC8AD27

#include <fftw3.h>

#include <Eigen/Dense>
#include <complex>
#include <unsupported/Eigen/FFT>
#include <vector>

namespace plasma {
/**
 * @brief Convert a vector to an eigen matrix object
 *
 * @tparam T the data type of the vector elements
 * @param data Data to be converted
 */
template <typename T>
inline static Eigen::Matrix<T, Eigen::Dynamic, 1> toEigen(
    const std::vector<T> &data) {
  Eigen::Matrix<T, Eigen::Dynamic, 1> M(data.size(), 1);
  for (size_t i = 0; i < data.size(); i++) M(i) = data[i];
  return M;
}

/**
 * @brief Convert a vector of vectors to an eigen matrix object
 *
 * @tparam T the data type of the vector elements
 * @param data Data to be converted
 */
template <typename T>
inline static Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> toEigen(
    const std::vector<std::vector<T>> &data) {
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> M(data.size(),
                                                     data.front().size());
  for (size_t i = 0; i < data.size(); i++)
    for (size_t j = 0; j < data.front().size(); j++) M(i, j) = data[i][j];
  return M;
}

/**
 * @brief Convert an eigen matrix object to a vector (or vector of vectors)
 *
 * @tparam Scalar Data type of the matrix elements
 * @tparam Matrix Matrix type to convert
 * @param M Input eigen matrix
 * @return std::vector< std::vector<Scalar>> Output vector
 */
template <typename Scalar, typename Matrix>
inline static std::vector<std::vector<Scalar>> fromEigen(const Matrix &M) {
  std::vector<std::vector<Scalar>> m(M.rows(), std::vector<Scalar>(M.cols()));
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.front().size(); j++) m[i][j] = M(i, j);
  return m;
}

/**
 * @brief Matlab-like syntax for computing a forward FFT with FFTW3
 *
 * @tparam T Input type
 * @param in Input data vector
 * @return std::vector<std::complex<double>> DFT of the input
 */
template <typename T>
std::vector<std::complex<double>> fft(const std::vector<T> &in) {
  Eigen::FFT<T> fft;
  std::vector<std::complex<double>> result;
  fft.fwd(result, in);
  return result;
}

/**
 * @brief Matlab-like syntax for computing a forward FFT with FFTW3
 *
 * @tparam T Input type
 * @param in Input data vector
 * @param N FFT length
 * @return std::vector<std::complex<double>>
 */
template <typename T>
std::vector<std::complex<double>> fft(const std::vector<T> &in, const int N) {
  // Resize the input vector
  std::vector<T> inPad = in;
  inPad.resize(N);
  Eigen::FFT<T> fft;
  // Compute and return the forward FFT
  std::vector<std::complex<double>> result;
  fft.fwd(result, inPad);
  return result;
}

/**
 * @brief Shift the zero frequency component to the center of the spectrum
 *
 * @tparam T Input vector element data type
 * @param in Input vector
 * @return std::vector<T> Shifted output vector
 */
template <typename T>
static std::vector<T> fftshift(std::vector<T> in) {
  auto out = in;
  auto len = out.size();
  auto center = (int)floor(len / 2);
  if (len % 2 != 0) center++;
  std::rotate(out.begin(), out.begin() + center, out.end());
  return out;
}

/**
 * @brief Inverse zero-frequency component shift
 *
 * @tparam T Input vector element data type
 * @param in Input vector
 * @return std::vector<T> Shifted output vector
 */
template <typename T>
static std::vector<T> ifftshift(std::vector<T> in) {
  auto out = in;
  auto len = out.size();
  auto center = (int)floor(len / 2);
  std::rotate(out.begin(), out.begin() + center, out.end());
  return out;
}

/**
 * @brief Compute the 1D convolution of two input vectors
 *
 * @tparam T Input data type
 * @param in1 1st input vector
 * @param in2 2nd input vector
 * @return std::vector<T> Convolution of the two input vectors with length
 * length(in1)+length(in2)-1
 */
template <typename T>
std::vector<T> conv(const std::vector<T> &in1, const std::vector<T> &in2) {
  // TODO: Do this with the fft() function defined in this file
  
  std::vector<std::complex<double>> fin1, fin2, product;
  std::vector<T> result;
  // Convolution length
  size_t N = in1.size() + in2.size() - 1;
  // Multiply the inputs in the frequency domain
  fin1 = fft(in1,N);
  fin2 = fft(in2,N);
  std::transform(fin1.begin(), fin1.end(), fin2.begin(),
                 std::back_inserter(product),
                 std::multiplies<std::complex<double>>());
  Eigen::FFT<T> fft;
  // Inverse FFT of the product
  fft.inv(result, product);
  return result;
}

/**
 * @brief Filter the data in vector x with the filter described by A and B
 *
 * The input-output description of the filter on a vector in the Z-transform
 * domain is a rational transfer function:
 *
 * Y(z) = (b[1]+b[2]z^-1+...+b[nb+1]z^-nb)/(1+a[1]z^-1+...+a[na+1]z^-na)X(z)
 *
 * where na is the feedback (IIR) filter order, nb is the feedforward (FIR)
 * filter order
 *
 * @tparam T Input type
 * @param b Numerator filter coefficients
 * @param a Denominator filter coefficients
 * @param x Input vector
 * @return std::vector<T> Filtered output vector
 */
template <typename T>
std::vector<T> filter(const std::vector<T> &b, const std::vector<T> &a,
                    const std::vector<T> &x) {
  // TODO: Make IIR filters work
  // Compute the filter response as a difference equation
  auto y = std::vector<T>(x.size());
  for (int i = 0; i < x.size(); i++) {
    y[i] = 0;
    for (int j = 0; j < std::min((int)b.size(), i + 1); j++) {
      y[i] += b[j] * x[i - j];
    }
  }
  return y;
}

/**
 * @brief Convert the input vector from linear scale to db
 *
 * TODO: Add a parameter for power vs voltage quantities
 *
 * @tparam T Element type of the input vector
 * @param in Input data
 * @return std::vector<T> Output data
 */
template <typename T>
static std::vector<T> db(std::vector<T> &in) {
  auto out = in;
  std::transform(out.begin(), out.end(), out.begin(),
                 [](T &x) { return 10 * log10(x); });
  return out;
}
}  // namespace plasma

#endif /* B5F351BB_C14A_43DF_A96F_0159BAC8AD27 */
