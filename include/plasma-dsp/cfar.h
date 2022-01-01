#ifndef D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#define D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#include <complex>
#include <vector>

namespace plasma {
/**
 * @brief Perform 1D cell-averaging CFAR detection on the input data vector
 * 
 * TODO: Create a CFAR class
 * TODO: Implement 2D CFAR for range-doppler maps
 * 
 * @param map 
 * @return std::vector<double> 
 */
std::vector<double> CACFAR(std::vector<std::complex<double>> &in);
}
#endif /* D4D7CDC7_8DAA_42DF_A71A_3840A89194E5 */
