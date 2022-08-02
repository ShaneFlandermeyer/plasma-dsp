// #include "parc.h" may need to include parc in cmake executable thingy as well
#include "cpm.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <arrayfire.h>

using namespace plasma;

int main() {

    // Create PARC object that takes two waveform objects in its constructor

    // af::array text(u8);
    // text.as(f32); // type casting in array fire
    double prf = 3e3;
    double samp_rate = 150e6;

    int num_symbols = 16;
    int num_samp_symbol = 8; // oversampling factor
    // a 2 dimensional array of random values ranging from -pi to pi
    // af::array comms = (2*M_PI) * af::randu(num_symbols,f32) - M_PI;

    std::ofstream wfile;
    wfile.open("test.txt");
    wfile << "Hello, world!";
    wfile.close();
     
    std::ifstream rfile ("test.txt");
    float arr[num_symbols] = {};

    if (rfile.is_open()) {
        for(int count = 0; rfile || (count <= num_symbols); count++){
            arr[count] = float(rfile.get());
        }
    }
    else { std::cout << "File not opened"; }

    af::array comms(num_symbols,1,arr);

    af::array filter = af::constant(1, num_samp_symbol);

    plasma::CPMWaveform cpm(filter, comms, samp_rate, num_samp_symbol);

    af::array cpm_arr = cpm.sample().as(c32);

    // std::string str = "New text for CPM";
    // for (int count = 0; count < num_symbols; count++){
    //     arr[count] = str[count];
    // }
    // af::array comms2(num_symbols,1,arr);
    // cpm.setMsg(comms2);
    // af::array cpm_arr2 = cpm.sample().as(c32);

    af::Window win;
    win.grid(1,1);
    af::array x = af::range(cpm_arr.elements());
    do {
        win(0,0).plot(x, af::real(cpm_arr));
        // win(0,0).plot(x, af::real(cpm_arr2));
        win.show();

    } while (not win.close());

    return EXIT_SUCCESS;
}