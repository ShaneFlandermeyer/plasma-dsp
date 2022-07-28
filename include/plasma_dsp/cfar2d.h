#ifndef A775376E_2D30_4128_8EC3_7F3F35F6FD7A
#define A775376E_2D30_4128_8EC3_7F3F35F6FD7A

#include "detector.h"
#include <array>
#include <arrayfire.h>

namespace plasma {
/**
 * @brief 2D Constant False Alarm Rate (CFAR) detector object.
 *
 * TODO: Currently only implements cell-averaging CFAR.
 *
 */
class CFARDetector2D {
public:
  /**
   * @brief Construct a new CFARDetector object.
   *
   */
  CFARDetector2D() = default;

  /**
   * @brief Construct a new CFARDetector object.
   *
   * @param cfar CFARDetector object.
   */
  CFARDetector2D(const CFARDetector2D &cfar) = default;

  /**
   * @brief Construct a new CFARDetector object.
   *
   * @param size_guard Number of guard cells surrounding the cell under test
   * in each dimension.
   * @param size_train Number of train cells surrounding the cell under test
   * in each dimension.
   * @param pfa Probability of false alarm
   */
  CFARDetector2D(size_t size_guard, size_t size_train, double pfa);

  /**
   * @brief Construct a new CFARDetector2D object.
   *
   * @param guard_win_size An array where the first element specifies the guard
   * band size along the row dimension (height) and the second element specifies
   * the gurad band size along the column dimension (width).
   *
   * @param train_win_size An array where the first element specifies the
   * training band size along the row dimension (height) and the second element
   * specifies the training band size along the column dimension (width).
   *
   * @param pfa Probability of false alarm.
   */
  CFARDetector2D(const std::array<size_t, 2> &guard_win_size,
                 const std::array<size_t, 2> &train_win_size, double pfa);

  /**
   * @brief Perform CFAR detections on the specified elements of the input data.
   *
   * @param x M-by-N matrix of real-valued input data.
   *
   * @return  DetectionReport.
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
   * size along the column dimension (width).
   *
   */
  std::array<size_t, 2> d_guard_win_size;

  /**
   * @brief The number of rows and columns of the training band cells on each
   * side of the CUT cell, specified as nonnegative integers.
   *
   * A array where the first element specifies the training band size
   * along the row dimension (height) and the second element specifies the guard
   * band size along the column dimension (width).
   *
   */
  std::array<size_t, 2> d_train_win_size;

  /**
   * @brief Probability of false alarm.
   *
   */
  double d_pfa;
};

} // namespace plasma

#endif /* A775376E_2D30_4128_8EC3_7F3F35F6FD7A */
