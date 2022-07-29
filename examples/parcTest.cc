// #include "parc.h" may need to include parc in cmake executable thingy as well
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
    double prf = 3e3;
    double samp_rate = 150e6;
    double bandwidth = 75e6;

    int num_symbols = 16;
    int num_samp_symbol = 6; // oversampling factor
    // a 2 dimensional array of random values ranging from -pi to pi
    af::array comms = (2*M_PI) * af::randu(num_symbols,f32) - M_PI;
    af::array filter = af::constant(1, num_samp_symbol);

    plasma::CPMWaveform cpm(filter, comms, samp_rate, num_samp_symbol);

    af::array cpm_arr = cpm.sample().as(c32);
    // cpm_arr.setMsg(new_msg);
    // to set new bits; use setMsg function or void comms function? Do they do the same thing?

    std::cout << "Created everything successfully!" << std::endl;

    // af::Window win;
    // af::array x = af::range(cpm_arr.elements());
    // do {
    //     win.plot(x, af::real(cpm_arr));

    // } while (not win.close());



    return EXIT_SUCCESS;
    
}