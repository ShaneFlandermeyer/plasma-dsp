#include "phase_code.h"

namespace plasma {
/**
 * @brief Generate a barker code of length n
 *
 * @param n Code length
 * @return std::vector<double> Barker code phase values
 */
std::vector<double> barker(int n) {
  std::vector<double> code;
  switch (n) {
  case 2:
    code = {0, 1};
    break;
  case 3:
    code = {0, 0, 1};
    break;
  case 4:
    code = {0, 0, 0, 1};
    break;
  case 5:
    code = {0, 0, 0, 1, 0};
    break;
  case 7:
    code = {0, 0, 0, 1, 1, 0, 1};
    break;
  case 11:
    code = {0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1};
    break;
  case 13:
    code = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0};
    break;
  default:
    throw std::invalid_argument("Invalid barker code length: " +
                                std::to_string(n));
  }
  for (auto &c : code) {
    c *= M_PI;
  }
  return code;
}

/**
 * @brief Generate a Frank code of (perfect square) length-M
 *
 * @param M Code length
 * @return std::vector<double>
 */
std::vector<double> frank(int M) {
  // Check that M is a perfect square (i.e., L is an integer)
  int L = std::round(std::sqrt(M));
  if (L * L != M)
    throw std::invalid_argument("Code length must be a perfect square");
  // Generate the code
  std::vector<double> code(M);
  for (auto n = 0; n < L; n++) {
    for (auto k = 0; k < L; k++) {
      code[n * L + k] = std::fmod((2 * M_PI / L) * (n * k), 2 * M_PI);
    }
  }
  return code;
}

std::vector<double> p4(int M) {
  std::vector<double> phi(M);
  for (int m = 0; m < M; m++) {
    phi[m] = 2 * M_PI / M * (m - 1) * (m - 1 - M) / 2;
  }
  return phi;
}

std::vector<double> PhaseCode::generate_code(Code code_type, int n) {
  if (n < 0)
    throw std::invalid_argument("Code length must be positive");
  std::vector<double> code;
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