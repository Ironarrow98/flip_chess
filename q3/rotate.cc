#include "rotate.h"
#include <vector>

using namespace std;

Rotate::Rotate(Image* i):Decorator{i} {}

void Rotate::render(PPM &ppm) {
  component->render(ppm);
  vector<Pixel> newPixel;
  vector<Pixel> pixels = ppm.getPixels();
  int size = (ppm.getPixels()).size();
  for(int i = 0; i < size; i++) {
    newPixel.emplace_back(pixels[i]);
  }
  int h = ppm.getHeight();
  int w = ppm.getWidth();
  for(int j = 0; j < (ppm.getHeight()); j++) {
    for(int i = 0; i < (ppm.getWidth()); i++) {
      (ppm.getPixels())[i * h + j] = newPixel[w * (h - j - 1) + i];
    }
  }
  ppm.getHeight() = w;
  ppm.getWidth() = h;
}

