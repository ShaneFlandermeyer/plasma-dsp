#include "parc.h"
#include <iostream>

namespace plasma {

PARCWaveform::PARCWaveform(af::array radar, af::array comm) {
  d_radar = radar;
  d_comm = comm;
}

af::array PARCWaveform::sample() {

    af::array parc = d_radar * d_comm;
    return parc;
}

af::array PARCWaveform::demod(const af::array &in) {
  auto ref = sample();
  return af::conjg(in) * ref;
}

} // namespace plasma