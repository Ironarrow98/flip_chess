#include "sepia.h"
#include <vector>

using namespace std;

int min(int x, int y) {
  if(x >= y) {
    return y;
  }
  return x;
}

Sepia::Sepia(Image* i):Decorator{i} {}

void Sepia::render(PPM &ppm) {
  component->render(ppm);
  vector<Pixel> pixels = ppm.getPixels();
  int size = pixels.size();
  for(int i = 0; i < size; i++) {
    int red = (pixels[i]).r;
    int green = (pixels[i]).g;
    int blue = (pixels[i]).b;
    ((ppm.getPixels())[i]).r = min(255, red *.393 + green * .769 + blue * .189);
    ((ppm.getPixels())[i]).g = min(255, red *.349 + green * .686 + blue * .168);
    ((ppm.getPixels())[i]).b = min(255, red *.272 + green * .534 + blue * .131);
  }
}

