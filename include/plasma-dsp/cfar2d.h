#ifndef A775376E_2D30_4128_8EC3_7F3F35F6FD7A
#define A775376E_2D30_4128_8EC3_7F3F35F6FD7A

#include <Eigen/Dense>

#ifdef USE_OPENMP
#include "omp.h"
#endif

namespace plasma {
  /**
 * @brief 2D Constant False Alarm Rate (CFAR) detector object
 *
 * TODO: Currently only implements cell-averaging CFAR.
 *
 */
class CFARDetector2D {
public:
  /**
   * @brief Construct a new CFARDetector object
   *
   */
  CFARDetector2D() = default;

  /**
   * @brief Construct a new CFARDetector object
   *
   * @param cfar CFARDetector object
   */
  CFARDetector2D(const CFARDetector2D &cfar) = default;

  /**
   * @brief Construct a new CFARDetector object
   *
   * @param size_train Number of training cells surrounding the cell under test
   * in each dimension
   * @param size_guard Number of guard cells surrounding the cell under test in
   * each dimension
   * @param pfa Probability of false alarm
   */
  CFARDetector2D(size_t size_train, size_t size_guard, double pfa);

  CFARDetector2D(Eigen::Array<size_t, 2, 1> size_guard,
                 Eigen::Array<size_t, 2, 1> size_train, double pfa);

  // /**
  //  * @brief Perform CFAR detection on the specified elements of the input data
  //  *
  //  *
  //  * @param x M-by-N matrix of real-valued input data, where M is the number of
  //  * range bins and N is the number of time instances in the input signal.
  //  * @param cut_row Zero-indexed row of the current cell under test (CUT)
  //  * @param cut_row Zero-indexed column of the current cell under test (CUT)
  //  * @return DetectionReport A struct containing
  //  *
  //  * - A logical matrix indicating whether a target was detected in each bin
  //  * - The CFAR threshold at each bin
  //  * - The matrix indices of each detection
  //  */
  // DetectionReport detect(const Eigen::MatrixXd &x, size_t cut_row, size_t cut_col);
  
  /**
   * @brief Perform CFAR detection on the specified matrix indices
   *
   * @param x Input data matrix
   * @param indices A 2-by-D
   * @return DetectionReport
   */
  DetectionReport detect(const Eigen::MatrixXd &x,
                         const Eigen::Array2Xi &indices);

  /**
   * @brief Perform CFAR detection on the entire input signal
   *
   * TODO: Enable tensor inputs
   *
   * @param x An M-by-1 matrix of real-valued input data.
   * @return std::vector<bool>
   */
  DetectionReport detect(const Eigen::MatrixXd &x);  

private:
  /**
   * @brief Perform CFAR detection on the specified elements of the input data
   *
   *
   * @param x M-by-N matrix of real-valued input data, where M is the number of
   * range bins and N is the number of time instances in the input signal.
   * @param cut_row Zero-indexed row of the current cell under test (CUT)
   * @param cut_row Zero-indexed column of the current cell under test (CUT)
   * @param result The detection report struct to be modified
   */
  void detect(const Eigen::MatrixXd &x, size_t cut_row, size_t cut_col,
              DetectionReport &result);

protected:
  /**
   * @brief The number of rows and columns of the guard band cells on each side
   * of the CUT cell, specified as nonnegative integers.
   *
   * A 2-by-1 array where the first element specifies the guard band size along
   * the row dimension (height) and the second element specifies the guard band
   * size along the column dimension (width)
   *
   */
  Eigen::Array<size_t, 2, 1> d_guard_win_size;

  /**
   * @brief The number of rows and columns of the training band cells on each
   * side of the CUT cell, specified as nonnegative integers.
   *
   * A 2-by-1 array where the first element specifies the training band size
   * along the row dimension (height) and the second element specifies the guard
   * band size along the column dimension (width)
   *
   */
  Eigen::Array<size_t, 2, 1> d_train_win_size;

  /**
   * @brief Probability of false alarm
   *
   */
  double d_pfa;
};

// /**
//  * @brief Compute the matrix indices of each detection from a detection
//  * report, and store them in the report struct
//  *
//  * @param result A DetectionReport object
//  */
// inline void ComputeCFARDetectionIndices(DetectionReport &result);
}

#endif /* A775376E_2D30_4128_8EC3_7F3F35F6FD7A */
