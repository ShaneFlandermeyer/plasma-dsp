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
   * @brief Rectangular window of length n
   * 
   * @param n 
   * @return std::vector<float> 
   */
  std::vector<double> rectangular(int n);

  /**
   * @brief blackman window of length n
   * 
   * @param n 
   * @return std::vector<double> 
   */
  std::vector<double> blackman(int n);



}  // namespace window