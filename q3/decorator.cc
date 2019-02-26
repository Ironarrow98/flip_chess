#include "decorator.h"

using namespace std;

Decorator::Decorator(Image* i) {
  component = i;
}

Decorator::~Decorator() {
  delete component;
}


