#ifndef __FLIP_H__
#define __FLIP_H__
#include "decorator.h"

class Flip : public Decorator {
public:
  Flip(Image* i);
  void render(PPM &ppm) override;
};

#endif
    