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

namespace plasma {

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

/**
 * @brief hamming window of length n
 *
 * @param n
 * @return std::vector<double>
 */
std::vector<double> hamming(int n);

/**
 * @brief hanning window of length n
 *
 * @param n
 * @return std::vector<double>
 */
std::vector<double> hanning(int n);

}  // namespace plasma

#endif /* E9175048_C018_4B5C_ACDB_4A0C0931BB61 */
