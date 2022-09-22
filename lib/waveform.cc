#include "waveform.h"

namespace plasma {

Waveform::Waveform() {
  d_samp_rate = 0;
  d_freq_offset = 0;
}

Waveform::Waveform(double samp_rate) {
  d_samp_rate = samp_rate;
  d_freq_offset = 0;
}

af::array Waveform::MatchedFilter() { return af::flip(af::conjg(sample()), 0); }

} // namespace plasma