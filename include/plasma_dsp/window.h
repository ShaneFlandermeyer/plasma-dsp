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
#include <arrayfire.h>

namespace plasma {
namespace window {

/**
 * @brief Rectangular window of length n
 *
 * @param n Window length
 * @return af::array
 */
af::array rectangular(int n);

/**
 * @brief blackman window of length n
 *
 * @param n Window length
 * @return std::vector<double>
 */
af::array blackman(int n);

/**
 * @brief hamming window of length n
 *
 * @param n Window length
 * @return std::vector<double>
 */
af::array hamming(int n);

/**
 * @brief hanning window of length n
 *
 * @param n Window length
 * @return std::vector<double>
 */
af::array hanning(int n);

af::array gaussian(int n, double alpha = 2.5);

} // namespace window
} // namespace plasma

#endif /* E9175048_C018_4B5C_ACDB_4A0C0931BB61 */
