#include "filter.h"
#include "linear_fm_waveform.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
static const size_t num_thread = std::thread::hardware_concurrency();

std::vector<std::complex<float>> read(const std::string &filename,
                                      size_t offset = 0) {
  std::ifstream infile(filename, std::ios::in | std::ios::binary);
  infile.seekg(0, std::ios::end);
  std::size_t nbytes = infile.tellg();
  std::size_t nitems = nbytes / sizeof(std::complex<float>);
  infile.seekg(offset, std::ios::beg);

  std::vector<std::complex<float>> data(nitems);
  infile.read(reinterpret_cast<char *>(data.data()), nbytes);
  infile.close();
  return data;
}

int main() {
  double bandwidth = 75e6;
  double pulse_width = 20e-6;
  double samp_rate = 100e6;
  size_t num_pulse_cpi = 1024;
  plasma::LinearFMWaveform waveform(bandwidth, pulse_width, 0, samp_rate);
  Eigen::ArrayXcf mf = waveform.MatchedFilter().cast<std::complex<float>>();

  // Load the waveform received by the SDR
  std::vector<std::complex<float>> data = read("/home/shane/pdu_data.dat");
  Eigen::ArrayXXcf x = Eigen::Map<Eigen::ArrayXcf>(data.data(), data.size())
                          .replicate(1, num_pulse_cpi);
  std::cout << "Fast-time/slow-time matrix size: " << x.rows() << "x"
            << x.cols() << std::endl;
  auto start = high_resolution_clock::now();
  Eigen::ArrayXXcf y = plasma::conv(x, mf, num_thread);
  std::cout << "Range/slow-time matrix size: " << y.rows() << "x"
            << y.cols() << std::endl;
  auto stop = high_resolution_clock::now();
  auto dt = duration<double>(stop - start).count();
  std::cout << "Time taken: " << dt << " seconds" << std::endl;

  std::cout << y.col(1) << std::endl;
}