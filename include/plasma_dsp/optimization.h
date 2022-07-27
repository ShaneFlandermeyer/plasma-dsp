#ifndef C7F3D66E_FFC1_488F_B9FF_CD881289EE71
#define C7F3D66E_FFC1_488F_B9FF_CD881289EE71

#include "constants.h"
#include "fft.h"
#include <arrayfire.h>

namespace plasma {

/**
 * @brief Use alternating projections to optimize a phase-coded waveform
 *
 * The equations used are derived from
 * https://ieeexplore.ieee.org/document/7485298
 *
 * @param in Input waveform
 * @param shape Desired spectral shape
 * @return af::array 
 */
af::array profm(const af::array &in, const af::array &shape);

} // namespace plasma

#endif /* C7F3D66E_FFC1_488F_B9FF_CD881289EE71 */
