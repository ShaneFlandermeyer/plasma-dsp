#ifndef AC67322C_687F_4BDC_8C4E_DD736C14C511
#define AC67322C_687F_4BDC_8C4E_DD736C14C511

#include <algorithm>
#include <complex>
#include <vector>
#include <fstream>

#include "constants.h"
namespace plasma {

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
Matrix<T> transpose(const Matrix<T> &in) {
  Matrix<T> out(in[0].size(), std::vector<T>(in.size()));
  for (size_t i = 0; i < in.size(); i++) {
    for (size_t j = 0; j < in[0].size(); j++) {
      out[j][i] = in[i][j];
    }
  }
  return out;
}

/**
 * @brief Compute the complex conjugate of each element in the input vector
 *
 *
 * @tparam T Input type
 * @param in Input data
 * @return std::vector<T> Conjugate of input
 */
template <typename T>
inline std::vector<T> conj(const std::vector<T> &in) {
  return in;
}

/**
 * @brief Compute the complex conjugate of each element in the input vector
 *
 *
 * @tparam T Input type
 * @param in Input data
 * @return std::vector<std::complex<double>> Conjugate of input
 */
template <typename T>
inline std::vector<std::complex<T>> conj(
    const std::vector<std::complex<T>> &in) {
  auto out = std::vector<std::complex<T>>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const auto &c) { return std::conj(c); });
  return out;
}

/**
 * @brief Element-wise absolute value of the input vector (real input)
 *
 * @tparam T
 * @param in
 * @return std::vector<T>
 */
template <typename T>
inline std::vector<T> abs(const std::vector<T> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const auto &x) { return std::abs(x); });
  return out;
}

/**
 * @brief Element-wise absolute value of the input vector (complex input)
 *
 * @tparam T
 * @param in
 * @return std::vector<T>
 */
template <typename T>
inline std::vector<T> abs(const std::vector<std::complex<T>> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const auto &x) { return std::abs(x); });
  return out;
}

/**
 * @brief Extract the real part of each element of the input vector
 *
 * @tparam T
 * @param in
 * @return std::vector<std::complex<T>>
 */
template <typename T>
inline std::vector<T> real(const std::vector<std::complex<T>> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const auto &x) { return std::real(x); });
  return out;
}

/**
 * @brief Extract the imaginary part of each element of the input vector
 *
 * @tparam T
 * @param in
 * @return std::vector<std::complex<T>>
 */
template <typename T>
inline std::vector<T> imag(const std::vector<std::complex<T>> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const auto &x) { return std::imag(x); });
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
inline std::vector<T> db(std::vector<T> in, DbUnit unit = DbUnit::VOLTAGE) {
  auto out = in;
  double factor;
  if (unit == DbUnit::VOLTAGE)
    factor = 20.0;
  else
    factor = 10.0;
  std::transform(out.begin(), out.end(), out.begin(),
                 [factor](const auto &x) { return factor * log10(x); });
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
inline Matrix<T> db(Matrix<T> in) {
  auto out = in;
  for (auto i_row = 0; i_row < in.size(); ++i_row) {
    std::transform(out[i_row].begin(), out[i_row].end(), out[i_row].begin(),
                   [](const auto &x) { return 10 * log10(x); });
  }
  // std::transform(out.begin(), out.end(), out.begin(),
  //                [](const auto &x) { return 10 * log10(x); });
  return out;
}

template <typename T>
inline void write_binary(const std::string &path, const std::vector<T> &data) {
  std::ofstream file(path, std::ios::out | std::ios::binary);
  file.write(reinterpret_cast<const char *>(data.data()),
             data.size() * sizeof(T));
  file.close();
}
}  // namespace plasma

#endif /* AC67322C_687F_4BDC_8C4E_DD736C14C511 */
