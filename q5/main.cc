#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"
#include "textdisplay.h"
#include "subject.h"
#include "observer.h"
#include "cell.h"

using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  bool black_turn = true;
  
  try {
    while (true) {
      cin >> cmd;
      if (cmd == "new") {
        int n;
        cin >> n;
        // Add code here
        g.init(n);
        cout << g;
        if(g.isFull()) {
          Colour colour = g.whoWon();
          if(colour == Colour::Black) {
            cout << "Black Wins!" << endl;
          } else if(colour == Colour::Black) {
            cout << "White Wins!" << endl;
          } else {
            cout << "Tie!" << endl;
          } 
        }
      } else if (cmd == "play") {
        int r = 0, c = 0;
        cin >> r >> c;
        // Add code here
        if(black_turn) {
          try {
            g.setPiece(r, c, Colour::Black);
            black_turn = false;
          } catch(InvalidMove i) {
            continue;
          }
        } else if(!black_turn) {
          try {
            g.setPiece(r, c, Colour::White);
            black_turn = true;
          } catch(InvalidMove i) {
            continue;
          }
        }
        cout << g;
        if(g.isFull()) {
          Colour colour = g.whoWon();
          if(colour == Colour::Black) {
            cout << "Black Wins!" << endl;
            break;
          } else if(colour == Colour::Black) {
            cout << "White Wins!" << endl;
            break;
          } else {
            cout << "Tie!" << endl;
            break;
          } 
        }
      }
    }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
