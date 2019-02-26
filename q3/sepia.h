#ifndef __SEPIA_H__
#define __SEPIA_H__
#include "decorator.h"

class Sepia : public Decorator {
public:
  Sepia(Image* i);
  void render(PPM &ppm) override;
};

#endif

