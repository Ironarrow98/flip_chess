#include "textdisplay.h"
#include <vector>

using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n} {
  theDisplay.clear();
  theDisplay.resize(n, vector<char>(n, '-'));
}

void TextDisplay::notify(Subject<Info, State>& whoNotified) {
  Info info = whoNotified.getInfo();
  Colour colour = info.colour;
  int r = info.row;
  int c = info.col;
  if(colour == Colour::Black) {
    (theDisplay[r])[c] = 'B';
  } else if(colour == Colour::White) {
    (theDisplay[r])[c] = 'W';
  } else {
    (theDisplay[r])[c] = '-';
  } 
}


std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (const auto& r : td.theDisplay) {
    for (auto c : r) {
      out << c;
    }
    out << endl;
  }
  return out;
}



