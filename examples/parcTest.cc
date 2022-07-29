#include "parc.h"
#include "cpm.h"
#include <iostream>
#include <vector>
#include <arrayfire.h>

using namespace plasma;

int main() {

    // Get CPM working with random float values
    // Create PARC object that takes two waveform objects in its constructor
    // Find out how to read data from a file and modulate it with a CPM waveform

    // af::array text(u8);
    // text.as(f32); // type casting in array fire
    double pulse_width = 10e-6;
    double prf = 3e3; // use or no use?
    double samp_rate = 150e6;
    double Ts = 1./samp_rate; // sampling interval
    double bandwidth = 75e6;

    num_rows = 4;
    num_cols = 4;
    k = 6; // oversampling factor
    // a 2 dimensional array of random values ranging from -pi to pi
    af::array comms = (2*M_PI) * af::randu(af::dim4(num_rows,num_cols),f32) - M_PI;
    af::array filter = af::constant(1, k*Ts);

    cpm = ::plasma::CPMWaveform(comms, filter, pulse_width, samp_rate, prf);
    af::array cpm_arr = cpm.sample().as(c32);
    //waveform.setBits(newComms);

    std::cout << "Created everything successfully!" << std::endl;



    return EXIT_SUCCESS;
    
}