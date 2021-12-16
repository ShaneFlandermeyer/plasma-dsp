#include "plasma-dsp/waveform.h"

Waveform::Waveform() {
  d_sampRate = 0;
}

Waveform::Waveform(double sampRate) {
  d_sampRate = sampRate;
}