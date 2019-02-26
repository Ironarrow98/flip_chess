#include "cell.h"
#include "state.h"
#include <assert.h>

using namespace std;

Cell::Cell(size_t rr, size_t cc): r(rr), c(cc), colour (Colour::None) {
    State s;
    s.colour = colour;
    s.type = StateType::NewPiece;
    s.direction = Direction::E;
    setState(s);
}

void Cell::setPiece(Colour cc) {
    assert(colour == Colour::None);
    colour = cc;
    State s;
    s.colour = colour;
    s.type = StateType::NewPiece;
    s.direction = Direction::E; // not used for NewPiece message
    setState(s);
    notify(*this);
}

void Cell::toggle() {
    colour = (colour == Colour::Black ? Colour::White : Colour::Black);
}

void Cell::notify(Subject<Info, State> &whoFrom) {
    if (colour == Colour::None) // return if empty
        return;

    auto info = whoFrom.getInfo(); // neighbor's info
    auto state = whoFrom.getState(); // state's colour is source colour
    Direction d[8] = { Direction::NW, Direction::N, Direction::NE, Direction::W,
                       Direction::E, Direction::SW, Direction::S, Direction::SE };
    int tx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int ty[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    auto ValidDirection = [&] (bool isReversDirection) {
        if (info.row == r && info.col == c) // source cell
            return false;
        for (int i = 0; i < 8; ++i) if (state.direction == d[i]) {
            if (isReversDirection) {
                return (r + tx[7 - i] == info.row && c + ty[7 - i] == info.col);
            }else {
                return (r + tx[i] == info.row && c + ty[i] == info.col);
            }
        }
        assert(false);
    };

    switch(state.type) {
    case StateType::NewPiece:
        // notify itself;
        if (r != info.row || c != info.col)
            break;
        assert(info.colour == state.colour);
        // relay others
        for (int i = 0; i < 8; ++i) {
            state.type = StateType::Relay;
            state.direction = d[i];
            setState(state);
            notifyObservers();
        }
        break;
    case StateType::Relay:
        if (ValidDirection(false)) {
            if (colour != state.colour) {
                setState(state);
                notifyObservers();
            } else {
                // reply
                state.type = StateType::Reply;
                setState(state);
                notifyObservers();
            }
        }
        break;
    case StateType::Reply:
        // return to source
        if (colour == state.colour) {
            break;
        }
        // others
        if (ValidDirection(true)) {
            toggle();
            setState(state);
            notifyObservers();
        }
        break;
    default:
        assert(false);
        break;
    }
}

Info Cell::getInfo() const {
    Info info;
    info.row = r;
    info.col = c;
    info.colour = colour;
    return info;
}