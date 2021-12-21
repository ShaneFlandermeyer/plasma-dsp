#include "utils.h"

namespace plasma {
// std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in) {
//   // FFT size
//   auto n = in.size();
//   // Output vector
//   std::vector<std::complex<double>> out(n);
//   // FFT plan
//   auto p = fftw_plan_dft_1d(n, reinterpret_cast<fftw_complex *>(&in[0]),
//                             reinterpret_cast<fftw_complex *>(&out[0]),
//                             FFTW_FORWARD, FFTW_ESTIMATE);
//   fftw_execute(p);
//   fftw_destroy_plan(p);
//   return out;
// }

// std::vector<std::complex<double>> fft(std::vector<double> &in) {
//   // FFT size
//   auto n = in.size();
//   // Output vector
//   std::vector<std::complex<double>> out(n);
//   // FFT plan
//   auto p = fftw_plan_dft_r2c_1d(n, reinterpret_cast<double *>(&in[0]),
//                                 reinterpret_cast<fftw_complex *>(&out[0]),
//                                 FFTW_ESTIMATE);
//   fftw_execute(p);
//   fftw_destroy_plan(p);
//   return out;
// }
}