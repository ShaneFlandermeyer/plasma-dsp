#include "cfar2d.h"
#include "detector.h"
#include "file.h"
#include <fstream>
#include <iostream>
#include <numeric>
#include <arrayfire.h>

int main(int argc, char *argv[]) {
  int device = argc > 1 ? atoi(argv[1]) : 0;
  af::setDevice(device);
  af::info();

  //This filename needs to be changed if you want to test this out yourself.
  std::string filename = "/home/avery/Research  Folder/MatLab/rangeDopplerMap";
  std::vector<double> rdm = plasma::read<double>(filename);
  float copy_rdm[rdm.size()];
  for(int i=0; i<rdm.size(); ++i){
    copy_rdm[i] = rdm[i];
  }
  //Turned the range doppler map into an array.
  af::array RDM(200, 1024, copy_rdm);

  //Setting the CFAR Window. 2 for the guard and 4 for the training.
  plasma::CFARDetector2D cfarDetector(2, 4, 0.00001f);

  //Compute where a detection is and then create a (row,col) array to store all the detections.
  DetectionReport results = cfarDetector.detect(RDM);

  //Print the number of detections.
  std::cout << "\n" << results.indices.size() << std::endl;

  //Print all the detection's location.
  for (int i = 0; i < results.indices.size(); ++i) {
    std::vector<int> currentCoord = results.indices[i];
    std::cout << currentCoord[0] << ", " << currentCoord[1] << std::endl;
  }

  //Save the _detection array so that matlab can read it.
  //The file location needs to be changed. Change it to where you want to store the results
  af::saveArray("", results._detection.as(u8), "/home/avery/Research  Folder/MatLab/cpp_detection");

  return 0;
}