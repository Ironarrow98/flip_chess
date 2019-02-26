#include "grid.h"
#include "textdisplay.h"

using namespace std;

Grid::~Grid() {
    Close();
}

void Grid::Close() {
    theGrid.resize(0);
    if (td != nullptr) {
        delete td;
        td = nullptr;
    }
    if (ob != nullptr) {
        delete ob;
        ob = nullptr;
    }
}

void Grid::setObserver(Observer<Info, State> *ob) {
    // TODO
}

bool Grid::isFull() const {
    for (const auto& rows : theGrid) {
        for (const auto& c : rows) {
            if (c.getInfo().colour == Colour::None) {
                return false;
            }
        }
    }
    return true;
}

Colour Grid::whoWon() const {
    int cntB = 0, cntW = 0;
    for (const auto& rows : theGrid) {
        for (const auto& c : rows) {
            cntB += (c.getInfo().colour == Colour::Black);
            cntW += (c.getInfo().colour == Colour::White);
        }
    }
    if (cntB == cntW)
        return Colour::None;
    return ((cntB > cntW) ? Colour::Black : Colour::White);
}

void Grid::init(size_t n) {
    Close();

    ob = nullptr;
    td = new TextDisplay(n);

    theGrid.resize(n, vector<Cell>());
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            theGrid[i].push_back(Cell(i, j));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            theGrid[i][j].attach(td);
            for (int r = i - 1; r <= i + 1; ++r) {
                for (int c = j - 1; c <= j + 1; ++c) if (0 <= r && r < n && 0 <= c && c < n) {
                    theGrid[i][j].attach(&theGrid[r][c]);
                }
            }
        }
    }
    int r = n / 2 - 1;
    int c = r;
    theGrid[r][c].setPiece(Colour::Black);
    theGrid[r + 1][c + 1].setPiece(Colour::Black);
    theGrid[r + 1][c].setPiece(Colour::White);
    theGrid[r][c + 1].setPiece(Colour::White);
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
    if (theGrid.empty())
        return;
    if (r < 0 || r >= theGrid.size() || c < 0 || c >= theGrid[0].size())
        return;
    if (theGrid[r][c].getInfo().colour != Colour::None)
        return;
    theGrid[r][c].setPiece(colour); // cell state change
}

void Grid::toggle(size_t r, size_t c) {
    theGrid[r][c].toggle();
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *g.td;
    return out;
}
