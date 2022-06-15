#include "fft.h"

int main() { 
  plasma::FFT<std::complex<float>> fft(1024, 1);
  fft.execute();

  return 0; 
}