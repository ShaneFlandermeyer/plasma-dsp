#ifndef B5F351BB_C14A_43DF_A96F_0159BAC8AD27
#define B5F351BB_C14A_43DF_A96F_0159BAC8AD27

#include <fftw3.h>

#include <Eigen/Dense>
#include <complex>
#include <vector>

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
 * @brief Matlab-like syntax for computing a complex forward FFT with FFTW3
 *
 * @param in Input data
 * @return std::vector<std::complex<double>> Complex DFT of the input
 */
std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in);

/**
 * @brief Matlab-like syntax for computing a real forward FFT with FFTW3
 *
 * @param in Input data
 * @return std::vector<std::complex<double>> Complex DFT of the input
 */
std::vector<std::complex<double>> fft(std::vector<double> &in);

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

#endif /* B5F351BB_C14A_43DF_A96F_0159BAC8AD27 */
