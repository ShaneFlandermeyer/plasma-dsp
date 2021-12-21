#include "waveform.h"

namespace plasma {

Waveform::Waveform() { d_sampRate = 0; }

Waveform::Waveform(double sampRate) { d_sampRate = sampRate; }
}  // namespace plasma