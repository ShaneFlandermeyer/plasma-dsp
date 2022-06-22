#ifndef ECB27E48_2453_4D30_917A_F02981F9C37C
#define ECB27E48_2453_4D30_917A_F02981F9C37C

#include <Eigen/Dense>

namespace plasma {
  
template <typename T>
using MatrixX = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

/**
 * @brief Horizontally concatenate two matrices
 *
 * @tparam T Element data type
 * @param A M x N left matrix
 * @param B M x P right matrix
 * @return MatrixX<T> M x (N + P) concatenated matrix
 */
template <typename T>
T hcat(const Eigen::EigenBase<T> &A, const Eigen::EigenBase<T> &B) {
  T out(A.rows(), A.cols()+B.cols());
  out.leftCols(A.cols()) = A;
  out.rightCols(B.cols()) = B;
  return out;
}

/**
 * @brief Vertically concatenate two matrices
 *
 * @tparam T Element data type
 * @param A M x P Top matrix
 * @param B N x P bottom matrix
 * @return MatrixX<T> (M + N) x P concatenated matrix
 */
template <typename T>
T vcat(const Eigen::EigenBase<T> &A, const Eigen::EigenBase<T> &B) {
  T out(A.rows() + B.rows(), A.cols());
  out.topRows(A.rows()) = A;
  out.bottomRows(B.rows()) = B;
  return out;
}

} // namespace plasma


#endif /* ECB27E48_2453_4D30_917A_F02981F9C37C */
