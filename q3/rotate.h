#ifndef __ROTATE_H__
#define __ROTATE_H__
#include "decorator.h"

class Rotate : public Decorator {
public:
  Rotate(Image* i);
  void render(PPM &ppm) override;
};

#endif
  