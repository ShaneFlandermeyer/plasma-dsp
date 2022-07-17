#include "phase_coded_waveform.h"
#include <iostream>
#include <arrayfire.h>
#include <complex>
#include <memory>
#include "phase_code.h"

int main() {
  af_print(plasma::PhaseCode::generate_code(plasma::PhaseCode::P4, 50));

  

  return 0;
}