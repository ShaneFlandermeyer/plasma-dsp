#ifndef A775376E_2D30_4128_8EC3_7F3F35F6FD7A
#define A775376E_2D30_4128_8EC3_7F3F35F6FD7A

#include "detector.h"
#include <arrayfire.h>

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
  CFARDetector2D(size_t size_guard, size_t size_train, float pfa);

  CFARDetector2D(int *gurad_win, int *train_size, float pfa);

  /**
   * @brief Perform CFAR detections on the specified elements of the input data
   * 
   * @param x M-by-N matrix of real-valued input data
   * @return af::array DetectionReport
   */
  DetectionReport detect(const af::array &x);

private:

protected:
  /**
   * @brief The number of rows and columns of the guard band cells on each side
   * of the CUT cell, specified as nonnegative integers.
   *
   * A array where the first element specifies the guard band size along
   * the row dimension (height) and the second element specifies the guard band
   * size along the column dimension (width)
   *
   */
  int d_guard_win_size[2];

  /**
   * @brief The number of rows and columns of the training band cells on each
   * side of the CUT cell, specified as nonnegative integers.
   *
   * A array where the first element specifies the training band size
   * along the row dimension (height) and the second element specifies the guard
   * band size along the column dimension (width)
   *
   */
  int d_train_win_size[2];

  /**
   * @brief Probability of false alarm
   *
   */
  float d_pfa;
};

// /**
//  * @brief Compute the matrix indices of each detection from a detection
//  * report, and store them in the report struct
//  *
//  * @param result A DetectionReport object
//  */
// inline void ComputeCFARDetectionIndices(DetectionReport &result);
} // namespace plasma

#endif /* A775376E_2D30_4128_8EC3_7F3F35F6FD7A */
