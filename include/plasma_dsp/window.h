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

#ifndef E9175048_C018_4B5C_ACDB_4A0C0931BB61
#define E9175048_C018_4B5C_ACDB_4A0C0931BB61
#include <vector>
#include <cmath>
#include <arrayfire.h>

namespace plasma {

/**
 * @brief Rectangular window of length n
 *
 * @param n Window length
 * @return af::array
 */
af::array rectangular(size_t n);

/**
 * @brief blackman window of length n
 *
 * @param n Window length
 * @return std::vector<double>
 */
af::array blackman(size_t n);

/**
 * @brief hamming window of length n
 *
 * @param n Window length
 * @return std::vector<double>
 */
af::array hamming(size_t n);

/**
 * @brief hanning window of length n
 *
 * @param n Window length
 * @return std::vector<double>
 */
af::array hanning(size_t n);

af::array gaussian(size_t n, double alpha = 2.5);

}  // namespace plasma

#endif /* E9175048_C018_4B5C_ACDB_4A0C0931BB61 */
