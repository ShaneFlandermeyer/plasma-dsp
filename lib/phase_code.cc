#include "phase_code.h"

namespace plasma {
/**
 * @brief Generate a barker code of length n
 *
 * See Radar Signals (Levanon, 2004) Ch. 6.1 for details
 *
 * @param n Code length
 * @return af::array
 */
af::array barker(int n) {
  std::vector<double> values;
  switch (n) {
  case 2:
    values = {0, 1};
    break;
  case 3:
    values = {0, 0, 1};
    break;
  case 4:
    values = {0, 0, 0, 1};
    break;
  case 5:
    values = {0, 0, 0, 1, 0};
    break;
  case 7:
    values = {0, 0, 0, 1, 1, 0, 1};
    break;
  case 11:
    values = {0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1};
    break;
  case 13:
    values = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0};
    break;
  default:
    throw std::invalid_argument("Invalid barker code length: " +
                                std::to_string(n));
  }
  af::array code(values.size(), f64);
  code.write(values.data(), values.size() * sizeof(double));
  code *= M_PI;
  return code;
}

/**
 * @brief Generate a Frank code of (perfect square) length-M
 *
 * See Radar Signals (Levanon, 2004) Ch. 6.2.1 for details
 *
 * @param M Code length
 * @return std::vector<double>
 */
af::array frank(int M) {
  // Check that M is a perfect square (i.e., L is an integer)
  int L = std::round(std::sqrt(M));
  if (L * L != M)
    throw std::invalid_argument("Code length must be a perfect square");
  // Generate the DFT matrix
  af::array n = af::seq(L);
  af::array k = af::seq(L);
  af::array dft_mat =
      af::tile(n, af::dim4(1, L)) * af::tile(k.T(), af::dim4(L, 1));
  // Generate the code
  af::array code(M);
  code = af::mod((2 * M_PI / L) * dft_mat, 2 * M_PI);
  return code;
}

/**
 * @brief Generate a P4 code of length M
 *
 * See Radar Signals (Levanon, 2004) Ch. 6.2.1 for details
 *
 * @param M Code length
 * @return std::vector<double>
 */
af::array p4(int M) {
  af::array code(M, f64);
  af::array m = af::seq(M);
  code = 2 * M_PI / M * (m - 1) * (m - 1 - M) / 2;
  code = af::mod(code, 2 * M_PI);
  return code;
}

af::array PhaseCode::generate_code(Code code_type, int n) {
  if (n < 0)
    throw std::invalid_argument("Code length must be positive");
  af::array code;
  switch (code_type) {
  case BARKER:
    code = barker(n);
    break;
  case FRANK:
    code = frank(n);
    break;
  case P4:
    code = p4(n);
    break;
  default:
    throw std::invalid_argument("Invalid phase code type");
    break;
  }
  return code;
}
} // namespace plasma