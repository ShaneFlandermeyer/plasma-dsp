#include <matplot/matplot.h>
#include <set>
#include <iostream>
#include "LinearFMWaveform.h"

int main() {
  // using namespace matplot;
  auto wave = LinearFMWaveform();
  std::cout << wave.prf << std::endl;
  return 0;
}