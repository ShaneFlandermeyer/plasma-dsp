#ifndef F9D71799_6DD6_49D7_89EC_155A8D8D6228
#define F9D71799_6DD6_49D7_89EC_155A8D8D6228

#include <vector> 
#include <numeric>
#include "pulsedwaveform.h"

class PCFMWaveform : public PulsedWaveform {
  protected:
    std::vector<double> d_code;
    std::vector<double> d_filter;


  public:
    PCFMWaveform();
    PCFMWaveform(const std::vector<double>& code, const std::vector<double>& filter);
    
    std::vector<std::complex<double>> pulse();
};
#endif /* F9D71799_6DD6_49D7_89EC_155A8D8D6228 */
