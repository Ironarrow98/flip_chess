#include "textdisplay.h"
#include "subject.h"
#include <assert.h>

using namespace std;

TextDisplay::TextDisplay(int n) : gridSize(n) {
    theDisplay.clear();
    theDisplay.resize(n, vector<char>(n, '-'));
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    auto info = whoNotified.getInfo();
    switch (info.colour) {
    case Colour::Black:
        theDisplay[info.row][info.col] = 'B';
        break;
    case Colour::White:
        theDisplay[info.row][info.col] = 'W';
        break;
    case Colour::None:
        theDisplay[info.row][info.col] = '-';
        break;
    default:
        assert(false);
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