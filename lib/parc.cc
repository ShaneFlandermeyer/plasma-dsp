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
  af::array comms = af::conjg(in) * ref;
  // af::array demoded_symbols = d_comms_waveform.demod(comms);
  return NULL;
}

} // namespace plasma