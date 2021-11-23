/**
 * @file window.h
 * @author Shane Flandermeyer (shaneflandermeyer@gmail.com)
 * @brief Defines common window functions.
 * @version 0.1
 * @date 2021-11-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <vector>

namespace window {

  /**
   * @brief Create a rectangular window of length n
   * 
   * @param n 
   * @return std::vector<float> 
   */
  std::vector<double> rectangular(int n);

}  // namespace window