#ifndef UTILS_H
#define UTILS_H

#include <fftw3.h>

#include <Eigen/Dense>
#include <complex>
#include <vector>

/**
 * @brief Convert a vector (or vector of vectors) to an eigen matrix object
 *
 * @tparam Scalar Data type of the matrix elements
 * @tparam Container Type of container storing the data
 * @param vectors Data to be converted
 * @return Eigen::Matrix<Scalar, -1, -1> Eigen matrix of the data
 */
template <typename Scalar, typename Container>
inline static Eigen::Matrix<Scalar, -1, -1> toEigen(const Container &vectors) {
  Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> M(
      vectors.size(), vectors.front().size());
  for (size_t i = 0; i < vectors.size(); i++)
    for (size_t j = 0; j < vectors.front().size(); j++) M(i, j) = vectors[i][j];
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

#endif