#include "parc.h"
#include "cpm.h"
#include "linear_fm_waveform.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <arrayfire.h>

using namespace plasma;

int main() {
    // af::array text(u8);
    // text.as(f32); // type casting in array fire
    double prf = 3e3;
    double samp_rate = 150e6;
    double bandwidth = 50e6;
    double pulse_width = 5e-6;

    int num_samp_symbol = 10; // oversampling factor
    // a 2 dimensional array of random values ranging from -pi to pi
    // length of cpm is oversampling factor * number of symbols 
    // length of lfm waveform is pulse width * sample rate

    std::ofstream wfile;
    wfile.open("test.txt");
    std::string str = "I want this to be 75 elements long so I am making this super looong string.";
    wfile << str;
    wfile.close();
   
    int num_symbols = str.size();
     
    std::ifstream rfile ("test.txt");
    float arr[num_symbols] = {};

    if (rfile.is_open()) {
        for(int count = 0; rfile || (count <= num_symbols); count++){
            arr[count] = float(rfile.get());
        }
    }
    else { std::cout << "File not opened!\n"; }

    af::array comms(num_symbols,1,arr);
    af::array filter = af::constant(1, num_samp_symbol);

    CPMWaveform cpm(filter, comms, samp_rate, num_samp_symbol);

    LinearFMWaveform lfm(bandwidth, pulse_width, samp_rate);

    af::array cpm_arr = cpm.sample().as(c32);

    af::array lfm_arr = lfm.sample().as(c32);

    PARCWaveform parc(lfm_arr,cpm_arr);

    af::array parc_arr = parc.sample().as(c32);

    af::Window win;
    win.grid(1,1);
    af::array x = af::range(parc_arr.elements());
    do {
        win(0,0).plot(x, af::imag(parc_arr));
        win.show();

    } while (not win.close());

    return EXIT_SUCCESS;
}
