#include "parc.h"
#include <iostream>

namespace plasma {

PARCWaveform::PARCWaveform(af::array radar, af::array comm) {
  d_radar = radar;
  d_comm = comm;
}

af::array PARCWaveform::sample() {
    int radar_size = d_radar.elements();
    int comms_size = d_comm.elements();

    if (radar_size == comms_size) {
      af::array parc = d_radar * d_comm;
      return parc;
    }
    else { 
      std::cout << "ERROR: Signals of length " << radar_size << 
        " and " << comms_size << " are not the same!\n";
      return af::constant(0,100);
    }
}

af::array PARCWaveform::demod(const af::array &in) {
  auto ref = sample();
  af::array comms = af::conjg(in) * ref;
  // af::array demoded_symbols = d_comms_waveform.demod(comms);
  return comms;
}

} // namespace plasma