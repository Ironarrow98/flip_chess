#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  bool isB = true;

  auto AfterMove = [&] () {
      cout << g << endl;
      if (g.isFull()) {
          auto c = g.whoWon();
          switch (c) {
          case Colour::Black:
              cout << "Black Wins!" << endl;
              break;
          case Colour::White:
              cout << "White Wins!" << endl;
              break;
          case Colour::None:
              cout << "Tie!" << endl;
              break;
          default:
              break;
          }
      }
  };

  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      // Add code here
      g.init(n);
      AfterMove();
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      // Add code here
      g.setPiece(r, c, isB ? Colour::Black : Colour::White);
      isB = 1 - isB;
      AfterMove();
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
