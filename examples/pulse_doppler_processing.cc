#include "fftshift.h"
#include "file.h"
#include "filter.h"
#include "linear_fm_waveform.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

using namespace std::chrono;
static const size_t num_thread = std::thread::hardware_concurrency();

int main() {

  double pulse_width = 20e-6;
  double samp_rate = 100e6;
  double bandwidth = 0.5 * samp_rate;
  double prf = 5e3;
  size_t num_pulse_cpi = 128;
  size_t num_samp_pri = samp_rate / prf;
  size_t num_samp_cpi = num_samp_pri * num_pulse_cpi;
  plasma::LinearFMWaveform waveform(bandwidth, pulse_width, 0, samp_rate);
  Eigen::ArrayXcf mf = waveform.MatchedFilter().cast<std::complex<float>>();
  // Load the waveform received by the SDR
  std::vector<std::complex<float>> data = plasma::read<std::complex<float>>(
      "/home/shane/test.dat", 0, num_samp_cpi);
  Eigen::ArrayXXcf fast_time_slow_time =
      Eigen::Map<Eigen::ArrayXXcf>(data.data(), data.size(), 1);
  fast_time_slow_time.resize(fast_time_slow_time.rows() / num_pulse_cpi,
                             num_pulse_cpi);

  Eigen::ArrayXXcf range_pulse_map =
      plasma::conv(fast_time_slow_time, mf, num_thread);
  std::cout << "Range/slow-time matrix size: " << range_pulse_map.rows() << "x"
            << range_pulse_map.cols() << std::endl;

  Eigen::ArrayXXcf range_dopp_map(range_pulse_map.rows(),
                                  range_pulse_map.cols());
  plasma::FFT<std::complex<float>, true> fft(range_pulse_map.cols(),
                                             num_thread);
  for (size_t i = 0; i < range_pulse_map.rows(); i++) {
    Eigen::ArrayXcf row = range_pulse_map.row(i);
    range_dopp_map.row(i) = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
        fft.execute(row.data()), row.size());
  }
  Eigen::ArrayXXcf rdm = range_dopp_map;

  // Write any data we can't process to a file
  std::ofstream out("/home/shane/pdu_file_sink_conv.dat");
  out.write((char *)range_pulse_map.data(),
            range_pulse_map.size() * sizeof(std::complex<float>));
  out.close();
  std::ofstream out2("/home/shane/rdm.dat");

  out2.write((char *)rdm.data(),
             rdm.size() * sizeof(std::complex<float>));
  out2.close();
}