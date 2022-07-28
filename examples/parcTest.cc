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

    af::array text(u8);
    text.as(f32); // type casting in array fire

    // a 2x2 array of random values from -pi to pi
    af::array vals = (2*M_PI) *af::randu(af::dim4(num_rows,num_cols),f32) - M_PI;

    af::array beta(100);
    PARCWaveform waveform;

    PCFMWaveform w1(...,...);
    CPMWaveform w2(...,...);

    PARCWaveform w3(w1,w2,comms);

    w3.sample();
    w3.setBits(newComms);
    w3.sample();






    std::cout << "Test" << std::endl;

    return EXIT_SUCCESS;
    
}