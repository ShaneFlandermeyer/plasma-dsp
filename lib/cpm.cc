#include "cpm.h"
#include <iostream>

namespace plasma {
CPMWaveform::CPMWaveform(af::array comms, af::array filter, 
    double pulse_width, double samp_rate, double prf) 
    : Waveform(samp_rate), PulsedWaveform(pulse_width,prf) 
     {
        d_comms = comms;
        d_filter = filter / af::sum<double>(filter); // normalize the filter for unit energy
    }

/*
    Convert byte-encoded text file to bits,
    apply L-REC (rectangular) CPM to it,
    element-wise multiply it with a base radar waveform (PCFM),
    transmit that!
*/
af::array CPMWaveform::sample() {

  double h = 1/2;
  // "Oversample" the phase difference code by a factor equal to the shaping
  // filter length. That is, for a length-n filter, the result is an n*code_size
  // vector where each nonzero element is a code value followed by n-1 zeros
  af::array train = af::constant(0, d_comms.elements() * d_filter.elements(), f64);
  train(af::seq(0, train.elements() - 1, d_filter.elements())) = d_comms;
  
  // Apply the shaping filter to the impulse train to "smooth out" the frequency
  // response
  af::array freq = af::fir(d_filter, train);

  // Integrate frequency to phase and exponentiate it to get the resulting
  // waveform
  af::array phase = af::accum(freq);
  phase *= (h*M_PI);
  af::array out = exp(af::Im * phase); 
  return out;
}


} // namespace plasma