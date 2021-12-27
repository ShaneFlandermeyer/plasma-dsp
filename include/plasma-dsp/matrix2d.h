#ifndef D7980583_8C42_4289_9C1D_9EC6487DFB3E
#define D7980583_8C42_4289_9C1D_9EC6487DFB3E
#include <iostream>
#include <stdexcept>
#include <vector>
/**
 * @brief Class representing a 2-dimensional matrix
 *
 * This class is primarly intended to provide an interface between STL vectors
 * and Eigen matrices. The data is stored in row-major order.
 *
 */
template <typename T>
class Matrix2D {
 public:
  /**
   * @brief Construct a new Matrix 2 D object
   *
   */
  Matrix2D();
  /**
   * @brief Construct a new Matrix 2 D object
   *
   * @param num_rows Number of rows
   * @param num_cols Number of columns
   */
  Matrix2D(unsigned int num_rows, unsigned int num_cols);
  /**
   * @brief Construct a new Matrix 2 D object
   *
   * @param num_rows Number of rows
   * @param num_cols Number of columns
   * @param values Vector of values
   */
  Matrix2D(unsigned int num_rows, unsigned int num_cols,
           const std::vector<T>& values);

  /**
   * @brief Return the element at the given (zero-indexed) row and column
   *
   * @param row Row index
   * @param col Column index
   * @return T& Element
   */
  T& operator()(unsigned int row, unsigned int col);

  template <typename Y>
  friend std::ostream& operator<<(std::ostream& os, const Matrix2D<Y>& mat);

  /**
   * @brief Return a pointer to the matrix data
   *
   * @return auto Pointer to the matrix data vector
   */
  auto data() const { return &d_data[0]; };

  /**
   * @brief Return the number of elements in the matrix
   *
   * @return auto Number of elements
   */
  auto numel() const { return &d_data.size(); };

  /**
   * @brief Return the number of rows in the matrix
   *
   * @return auto
   */
  auto rows() const { return d_num_rows; };

  /**
   * @brief Return the number of columns in the matrix
   *
   * @return auto
   */
  auto cols() const { return d_num_cols; };

 protected:
  /**
   * @brief Data vector
   *
   */
  std::vector<T> d_data;
  /**
   * @brief Number of rows
   *
   */
  unsigned int d_num_rows;
  /**
   * @brief Number of columns
   *
   */
  unsigned int d_num_cols;
};

template <typename T>
Matrix2D<T>::Matrix2D() {
  d_num_rows = 0;
  d_num_cols = 0;
  d_data = std::vector<T>(d_num_rows * d_num_cols, 0);
}

template <typename T>
Matrix2D<T>::Matrix2D(unsigned int num_rows, unsigned int num_cols) {
  d_num_rows = num_rows;
  d_num_cols = num_cols;
  d_data = std::vector<T>(d_num_rows * d_num_cols, 0);
}

template <typename T>
Matrix2D<T>::Matrix2D(unsigned int num_rows, unsigned int num_cols,
                      const std::vector<T>& values) {
  d_num_rows = num_rows;
  d_num_cols = num_cols;
  d_data = values;
}

template <typename T>
T& Matrix2D<T>::operator()(unsigned int row, unsigned int col) {
  if (row >= d_num_rows || col >= d_num_cols) {
    throw std::out_of_range("Matrix2D: index out of range");
  }
  return d_data[row * d_num_cols + col];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Matrix2D<T>& mat) {
  for (int row = 0; row < mat.rows(); row++) {
    for (int col = 0; col < mat.cols(); col++) {
      os << mat(row, col) << " ";
    }
    os << std::endl;
  }
  return os;
}

#endif /* D7980583_8C42_4289_9C1D_9EC6487DFB3E */
