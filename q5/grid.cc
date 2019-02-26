#include "grid.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <vector>
#include <iostream>
#include <sstream>
#undef None

using namespace std;


Grid::~Grid() {
  theGrid.clear();
  if(td != nullptr) {
    delete td;
    td = nullptr;
  }
  if(ob != nullptr) {
    delete ob;
    ob = nullptr;
  }
}


void Grid::setObserver(Observer<Info, State> *o) {
  ob = o;
}


bool Grid::isFull() const {
  for(const auto& r : theGrid) {
    for(const auto& c : r) {
      Info info = c.getInfo();
      if(info.colour == Colour::None) {
        return false;
      }
    }
  }
  return true;
}


Colour Grid::whoWon() const {
  int black = 0;
  int white = 0;
  for(const auto& r : theGrid) {
    for(const auto& c : r) {
      Info info = c.getInfo();
      if(info.colour == Colour::Black) {
        black++;
      } else if(info.colour == Colour::White) {
        white++;
      }
    }
  }
  if(black > white) {
    return Colour::Black;
  } else if(black < white) {
    return Colour::White;
  } else {
    return Colour::None;
  }
}


void Grid::init(size_t n) {
  theGrid.clear();
  if(td != nullptr) {
    delete td;
    td = nullptr;
  }
  if(ob != nullptr) {
    delete ob;
    ob = nullptr;
  }
  int m = n;
  td = new TextDisplay{m};
  Observer<Info, State>* ob = new GraphicsDisplay{m, 500};   // used for q5 when we need to create a new GraphicDisplay observer
  setObserver(ob);    // used for q5 when we need to create a new GraphicDisplay observer
  for(int i = 0; i < m; i++) {
    vector<Cell> v;
    for(int j = 0; j < m; j++) {
      v.emplace_back(Cell(i, j));
    }
    theGrid.emplace_back(v);
  }
  for(int i = 0; i < m; i++) { 
    for(int j = 0; j < m; j++) {
      (theGrid[i])[j].attach(td);    // attach new textdisplay observer into observers 
      (theGrid[i])[j].attach(ob);    // used for q5 when we need to attach the new GraphicDisplay observer into the observers
      for(int r = i - 1; r <= i + 1; r++) {
        for(int c = j - 1; c <= j + 1; c++) {
          if((0 <= r && r < m) && (0 <= c && c < m)) {
            (theGrid[i])[j].attach(&((theGrid[r])[c]));  // attach all its neighbours into observers
          }
        }
      }
    }
  }
  // set middle four pieces when initiallizing
  int r = m / 2 - 1;
  int c = r;
  (theGrid[r])[c].setPiece(Colour::Black);
  (theGrid[r + 1])[c + 1].setPiece(Colour::Black);
  (theGrid[r + 1])[c].setPiece(Colour::White);
  (theGrid[r])[c + 1].setPiece(Colour::White);
}


void Grid::setPiece(size_t r, size_t c, Colour colour) {
  int size = theGrid.size();
  int R = r;
  int C = c;
  if((0 <= R && R < size) && (0 <= C && C < size)) {
    Colour color = (theGrid[r])[c].getInfo().colour;
    if(color == Colour::None) {
      (theGrid[R])[C].setPiece(colour);
    } else {
      throw InvalidMove();
    }
  } else {
    throw InvalidMove();
  } 
}

void Grid::toggle(size_t r, size_t c) {
  ((theGrid[r])[c]).toggle();
}


ostream& operator<<(ostream& out, const Grid& g) {
  out << *g.td;
  return out;
} 



