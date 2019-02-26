#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include "state.h"
#include "info.h"


class Cell;


class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
 public:
  TextDisplay(int n);
  void notify(Subject<Info, State> &whoNotified) override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif

