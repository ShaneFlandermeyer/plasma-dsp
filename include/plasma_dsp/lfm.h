#ifndef BD5E6A09_B96F_4379_84DF_C755B8C14BF8
#define BD5E6A09_B96F_4379_84DF_C755B8C14BF8

#include "pulsed_waveform.h"
// #include <numeric>
#include <arrayfire.h>

namespace plasma {

af::array lfm(double start_freq, double bandwidth, double pulse_width,
              double samp_rate, double prf = 0);
              
} // namespace plasma
#endif /* BD5E6A09_B96F_4379_84DF_C755B8C14BF8 */
