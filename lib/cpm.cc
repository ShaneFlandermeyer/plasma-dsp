#include "cpm.h"
#include <iostream>

namespace plasma {
CPMWaveform::CPMWaveform(af::array filter, af::array comms, 
     double samp_rate, double num_samp_symbol, double prf) 
    : Waveform(samp_rate), PulsedWaveform((comms.elements() * filter.elements()) / samp_rate, prf) 
     {
        d_k = num_samp_symbol;
        d_comms = comms;
        d_filter = filter / af::sum<double>(filter); // normalize the filter for unit energy
    }

/*
    Creates one pulse of a Continuous Phase Modulated waveform
    encoded with a communications message
*/
af::array CPMWaveform::sample() {

  float d_h = 1./2; // modulation index 
  // "Oversample" tcommunications code by a factor of num_samp_symbol.
  // In other words, for a length-n comms message, the result is an num_samp_symbol*n
  // vector where each nonzero element is a comms value followed by n-1 zeros
  af::array train = af::constant(0, d_comms.elements() * d_k, f64);
  train(af::seq(0, train.elements()-1, d_k)) = d_comms;
  
  // Apply the shaping filter to the impulse train to "smooth out" the frequency
  // response
  af::array freq = af::fir(d_filter, train);

  // Integrate frequency to phase and exponentiate it to get the resulting
  // waveform
  af::array phase = af::accum(freq);
  phase *= (d_h*M_PI);
  af::array out = exp(af::Im * phase); 
  return out;
}

/*
    Modifies the communication message to be encoded in the CPM waveform.
*/
void CPMWaveform::setMsg(af::array msg) {

    d_comms = msg;
    return;
}

} // namespace plasma