#ifndef F76EB5C6_3C7E_46B6_AC56_C303873CDA4A
#define F76EB5C6_3C7E_46B6_AC56_C303873CDA4A

#include <vector>

#include "waveform.h"

class PhaseCodedWaveform : public Waveform {
 protected:
  int d_nChips;
  int d_chipwidth;
  std::vector<double> d_code;

 public:
  auto code() const {return d_code;}
  auto code(const std::vector<double>& code) {d_code = code;}
};

#endif /* F76EB5C6_3C7E_46B6_AC56_C303873CDA4A */
