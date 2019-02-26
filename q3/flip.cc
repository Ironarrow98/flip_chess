#include "flip.h"
#include <vector>

using namespace std;

Flip::Flip(Image* i):Decorator{i} {}

void Flip::render(PPM &ppm) {
  component->render(ppm);
  for(int i = 0; i < ppm.getHeight(); i++) {
    for(int j = 0; j < ((ppm.getWidth()) / 2); j++) {
      Pixel p = (ppm.getPixels())[i * (ppm.getWidth()) + j];
      (ppm.getPixels())[i * (ppm.getWidth()) + j] = (ppm.getPixels())[(i * (ppm.getWidth())) + ((ppm.getWidth()) - j - 1)];
      (ppm.getPixels())[(i * (ppm.getWidth())) + ((ppm.getWidth()) - j - 1)] = p;
    }
  }
}

 