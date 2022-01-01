/**
 * @brief Convert an eigen matrix into a vector of std vectors
 *
 * The only reason one generally wants to do this is to plot something with
 * matplot++
 *
 * @return std::vector<std::vector<Scalar>> 2d vector representing the eigen
 * matrix
 */
std::vector<Scalar> vector1d() {
  std::vector<Scalar> vec(this->size());
  for (size_t i = 0; i < this->rows(); i++) {
    for (size_t j = 0; j < this->cols(); j++) {
      vec[i*this->cols()+j] = this->operator()(i, j);
    }
  }
  return vec;
}

/**
 * @brief Convert an eigen matrix into a vector of std vectors
 *
 * The only reason one generally wants to do this is to plot something with
 * matplot++
 *
 * @return std::vector<std::vector<Scalar>> 2d vector representing the eigen
 * matrix
 */
std::vector<std::vector<Scalar>> vector2d() {
  std::vector<std::vector<Scalar>> vec(this->rows(),
                                       std::vector<Scalar>(this->cols()));
  for (uint i = 0; i < this->rows(); i++) {
    for (uint j = 0; j < this->cols(); j++) {
      vec[i][j] = this->operator()(i, j);
    }
  }
  return vec;
}

