#ifndef D62729DA_CADC_457A_97F7_1CF6F2287795
#define D62729DA_CADC_457A_97F7_1CF6F2287795

#include "pulsed_waveform.h"
#include <arrayfire.h>

namespace plasma {

class CPMWaveform: public PulsedWaveform{
private:

  /**
   * @brief Shaping filter
   *
   */
  af::array d_filter;

  /**
   * @brief Communications message
   *
   */
  af::array d_comms;

  /**
   * @brief Oversampling factor
   *
   */
  double d_k;

public:
  /**
   * @brief Construct a new PARCWaveform object
   *
   */
  CPMWaveform() = default;

  /**
   * @brief Construct a new CPMWaveform object
   *
   * @param filter Shaping filter
   * @param comms Communications message
   * @param samp_rate sample rate 
   * @param num_samp_symbol Oversampling factor (k or ns)
   * @param prf pulse repition frequency
   */
  CPMWaveform( af::array filter, af::array comms, double samp_rate, double num_samp_symbol = 6, double prf = 0);

  /**
   * @brief Destroy the CPMWaveform object
   *
   */
  ~CPMWaveform() = default;

  /**
   * @brief Generates non-zero samples for one pulse
   * 
   * @param comm The encoded communications message
   *
   * @return af::array the pulse samples
   */
  af::array sample() override;

  /**
   * @brief sets the comms message for a new waveform
   * 
   * @param comm The encoded communications message
   */
  void setMsg(af::array comm) {d_comms = comm;};

  /** 
   * @brief Get the shaping filter
   *
   * @return Shaping filter
   */
  af::array getFilter() const { return d_filter; }

  /**
   * @brief Set the shaping filter
   *
   * @param filt Desired shaping filter
   * @return auto The vector of filter taps
   */
  void setFilter(af::array filt) { d_filter = filt; }

  /**
   * @brief Get the comms message
   *
   * @return auto comms signal
   */
  af::array getMsg() const { return d_comms; }

};
} // namespace plasma

#endif /* D62729DA_CADC_457A_97F7_1CF6F2287795 */
