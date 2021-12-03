#include "phasecode.h"
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
    case 3:
      code = {0, 0, 1};
    case 4:
      code = {0, 0, 0, 1};
    case 5:
      code = {0, 0, 0, 1, 0};
    case 7:
      code = {0, 0, 0, 1, 1, 0, 1};
    case 11:
      code = {0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1};
    case 13:
      code = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0};
    default:
      throw std::invalid_argument(
          "Invalid barker code length: " + std::to_string(n));
  }
  // TODO: Convert this to a complex exponential
  return code;
}

std::vector<double> PhaseCode::generate_code(codeType type, int n) {
  std::vector<double> code;
  switch (type) {
    case BARKER:
      code = barker(n);
      break;
  }
  return code;
}