#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include "image.h"

class Decorator : public Image {
protected:
  Image* component;
public:
  Decorator(Image* i);
  virtual ~Decorator();
};

#endif

