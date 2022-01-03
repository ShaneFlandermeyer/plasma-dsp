#ifndef D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#define D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#include <complex>
#include <vector>
#include <Eigen/Dense>

namespace plasma {
// TODO: Make a CFAR object?

/**
 * @brief Constant False Alarm Rate (CFAR) detector object
 *
 * TODO: Currently only implements cell-averaging CFAR.
 * TODO: Currently only supports 1D CFAR.
 * TODO: Does not handle edge cases.
 *
 */
class CFARDetector {
public:
  /**
   * @brief Construct a new CFARDetector object
   *
   */
  CFARDetector() = default;
  /**
   * @brief Construct a new CFARDetector object
   *
   */
  CFARDetector(const CFARDetector &) = default;
  /**
   * @brief Construct a new CFARDetector object
   *
   * @param num_train Number of training cells
   * @param num_guard Number of guard cells
   * @param pfa Probability of false alarm
   */
  CFARDetector(size_t num_train, size_t num_guard, double pfa);
  /**
   * @brief Perform CFAR detection on the specified elements of the input data
   *
   * @param x M x N matrix of real-valued input data, where M is the number of
   * cells in the CFAR window and N is the number of samples.
   * @param cut_index Index of the current cell under test (CUT)
   * @return std::vector<bool> D x N matrix containing logical detection
   * results, where D is the length of cut_index and N is the number of rows in
   * x.
   */
  std::vector<bool> detect(const Eigen::MatrixXd &x, size_t cut_index);

protected:
  /**
   * @brief Number of guard cells on either side of the cell under test
   *
   */
  size_t d_num_guard_cells;
  /**
   * @brief Number of training cells on either side of the cell under test
   *
   */
  size_t d_num_train_cells;
  /**
   * @brief Probability of false alarm
   *
   */
  double d_pfa;
};

} // namespace plasma
#endif /* D4D7CDC7_8DAA_42DF_A71A_3840A89194E5 */
