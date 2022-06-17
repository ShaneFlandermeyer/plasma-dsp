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
  double bandwidth = 75e6;
  double pulse_width = 20e-6;
  double samp_rate = 100e6;
  double prf = 5e3;
  size_t num_pulse_cpi = 512;
  size_t num_samp_pri = samp_rate / prf;
  size_t num_samp_cpi = num_samp_pri * num_pulse_cpi;
  plasma::LinearFMWaveform waveform(bandwidth, pulse_width, 0, samp_rate);
  Eigen::ArrayXcf mf = waveform.MatchedFilter().cast<std::complex<float>>();
  // Load the waveform received by the SDR
  std::vector<std::complex<float>> data =
      plasma::read<std::complex<float>>("/home/shane/pdu_file_sink.dat", 0, num_samp_cpi);
  Eigen::ArrayXXcf x =
      Eigen::Map<Eigen::ArrayXXcf>(data.data(), data.size(), 1);
  x.resize(x.rows() / num_pulse_cpi, num_pulse_cpi);

  Eigen::ArrayXXcf y = plasma::conv(x, mf, num_thread);
  std::cout << "Range/slow-time matrix size: " << y.rows() << "x" << y.cols()
            << std::endl;
}