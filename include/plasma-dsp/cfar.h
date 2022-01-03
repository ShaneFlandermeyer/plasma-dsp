#ifndef D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#define D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#include <complex>
#include <vector>
#include <Eigen/Dense>

namespace plasma {
// TODO: Make a CFAR object?
/**
 * @brief Perform 1D CA-CFAR detection on a single cell under test (CUT).
 *
 *
 * @param x Matrix of input samples with size # of cells x # of trials
 * @param cut_index Vector index of cell under test (i.e., a row of x)
 * @return std::vector<bool> Vector with length = # of trials, where at each
 * element the result is true if there is a detection in the CUT and false
 * otherwise.
 */
std::vector<bool> cfar(Eigen::MatrixXd &x, size_t cut_index);
} // namespace plasma
#endif /* D4D7CDC7_8DAA_42DF_A71A_3840A89194E5 */
