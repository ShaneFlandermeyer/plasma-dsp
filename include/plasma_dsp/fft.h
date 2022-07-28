#ifndef DB2A4C4D_F60E_47B4_A002_0221B2108E21
#define DB2A4C4D_F60E_47B4_A002_0221B2108E21

#include <iostream>
#include <arrayfire.h>

namespace plasma {

/**
 * @brief Swap halves of the input array along a given dimension
 *
 * @param in Input array
 * @param dim shift dimension
 * @return af::array
 */
af::array fftshift(const af::array &in, int dim = -1);

/**
 * @brief Swap halves of the input array along a given dimension, such that the
 * effects of an fftshift along those dimensions are undone if performed
 * sequentially.
 *
 * @param in
 * @param dim
 * @return af::array
 */
af::array ifftshift(const af::array &in, int dim = -1);

} // namespace plasma

#endif /* DB2A4C4D_F60E_47B4_A002_0221B2108E21 */
