#include "cell.h"


using namespace std;


Cell::Cell(size_t r, size_t c): r{r}, c{c}, colour{Colour::None} {
  State newS;
  newS.colour = colour;
  newS.type = StateType::NewPiece;
  newS.direction = Direction::N;
  setState(newS);
}


void Cell::setPiece(Colour cc) {
  colour = cc;
  State newS;
  newS.colour = colour;
  newS.type = StateType::NewPiece;
  newS.direction = Direction::N;
  setState(newS);
  notifyObservers();
}


void Cell::toggle() {
  if(colour == Colour::Black) {
    colour = Colour::White;
  } else if(colour == Colour::White) {
    colour = Colour::Black;
  }
}


// To check if my travel direction is correct or not regard to Reply and Relay
bool directValid(bool reverse, Direction sd, Direction* d, int* rows, int* cols, int ir, int ic, int sr, int sc) {
  if(ir == sr && ic == sc) {
    return false;
  }
  for(int i = 0; i < 8; i++) {
    if(sd == d[i]) {
      if(reverse) {
        return (sr + rows[7 - i] == ir && sc + cols[7 - i] == ic);
      } else {
        return (sr + rows[i] == ir && sc + cols[i] == ic);
      }
    }
  }
  return false;
}
  

void Cell::notify(Subject<Info, State>& whoFrom) {
  if(colour == Colour::None) {
    // check the base case that if I am a valid cell or I am empty, if empty then do nothing and stop
    return;
  }
  Direction d[8] = {Direction::NW, Direction::N, Direction::NE, Direction::W, Direction::E, Direction::SW, Direction::S, Direction::SE};
  int rows[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int cols[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  State prestate = whoFrom.getState();
  Info preinfo = whoFrom.getInfo();
  // convert size_t type to int type
  int ir = preinfo.row;
  int ic = preinfo.col;
  int sr = r;
  int sc = c;
  if(prestate.type == StateType::Relay) {
    Direction direct = prestate.direction;
    bool b = directValid(false, direct, d, rows, cols, ir, ic, sr, sc);
    if(b) {
      if(colour != prestate.colour) {
        // keep Relay
        setState(prestate);
        notifyObservers();
      } else {
        // time to Reply
        prestate.type = StateType::Reply;
        setState(prestate);
        notifyObservers();
      }
    }
  } else if(prestate.type == StateType::Reply) {
    if(colour == preinfo.colour) {
      // Now it's on the original New Piece, time to stop Reply
      return;
    }
    Direction direct = prestate.direction;
    bool b = directValid(true, direct, d, rows, cols, ir, ic, sr, sc);
    if(b) {
      // keep Reply
      toggle();
      setState(prestate);
      notifyObservers();
    }
  } else {
    if(r != preinfo.row || c != preinfo.col) {
      // check if I am the NewPiece or not
      return;
    } 
    if(preinfo.colour == prestate.colour) {
      // notify all my neighbor I am a NewPiece, let them start Relay
      for(int i = 0; i < 8; i++) {
        prestate.type = StateType::Relay;
        prestate.direction = d[i];
        setState(prestate);
        notifyObservers();
      }
    }
  }
}


Info Cell::getInfo() const {
  Info i;
  i.row = r;
  i.col = c;
  i.colour = colour;
  return i;
}


