#ifndef D7980583_8C42_4289_9C1D_9EC6487DFB3E
#define D7980583_8C42_4289_9C1D_9EC6487DFB3E
#include <iostream>
#include <stdexcept>
#include <vector>
/**
 * @brief Class representing a 2-dimensional matrix
 *
 * This class is primarly intended to provide a convenient interface between STL
 * vectors and Eigen matrices. Eigen should be used where speed is critical.
 *
 * The data is stored in column-major order.
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

  /**
   * @brief Return a copy of the matrix data in the given column
   *
   * @param row The column index
   * @return std::vector<T>
   */
  const std::vector<T> col(unsigned int col);

  /**
   * @brief Return a copy of the matrix data in the given row
   *
   * @param row The row index
   * @return std::vector<T>
   */
  const std::vector<T> row(unsigned int row);

  /**
   * @brief Return a pointer to the matrix data
   *
   * @return auto Pointer to the matrix data vector
   */
  auto data() { return d_data.data(); };

  /**
   * @brief Return the number of elements in the matrix
   *
   * @return auto Number of elements
   */
  auto numel() const { return d_data.size(); };

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

  /**
   * @brief Type cast operator
   * 
   * Converts a Matrix2D object to a vector of vectors of the same type.
   * 
   * @return std::vector<std::vector<T>> 
   */
  operator std::vector<std::vector<T>>();

  /**
   * @brief Prints the matrix data to stdout
   * 
   * @tparam U Matrix element data type
   * @param os ostream object
   * @param mat Matrix2D object
   * @return std::ostream& 
   */
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Matrix2D<U>& mat);

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
  d_data = std::vector<T>(d_num_rows * d_num_cols, 0);
  for (int i = 0; i < values.size(); i++) {
    d_data[i] = values[i];
  }
}

template <typename T>
const std::vector<T> Matrix2D<T>::col(unsigned int col) {
  std::vector<T> out(d_num_rows);
  for (int i_row = 0; i_row < d_num_rows; i_row++) {
    out[i_row] = (*this)(i_row, col);
  }
  return out;
}

template <typename T>
const std::vector<T> Matrix2D<T>::row(unsigned int row) {
  std::vector<T> out(d_num_cols);
  for (int i_col = 0; i_col < d_num_cols; i_col++) {
    out[i_col] = (*this)(row, i_col);
  }
  return out;
}

template <typename T>
T& Matrix2D<T>::operator()(unsigned int row, unsigned int col) {
  if (row >= d_num_rows || col >= d_num_cols) {
    throw std::out_of_range("Matrix2D: index out of range");
  }
  return d_data[col * d_num_rows + row];
}

template <typename T>
Matrix2D<T>::operator std::vector<std::vector<T>>() {
  std::vector<std::vector<T>> out(d_num_rows);
  for (int i_row = 0; i_row < d_num_rows; i_row++) {
    out[i_row] = row(i_row);
  }
  return out;
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
