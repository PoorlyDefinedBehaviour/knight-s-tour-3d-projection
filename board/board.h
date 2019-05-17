#pragma once
#include "../cell/cell.h"

class Board
{
private:
    int size = 7;
    Cell **elements = nullptr;

public:
    Board();
    ~Board();
    void resize(int size);
    int get_size() const noexcept;
    void visit(int row, int column);
    bool is_visited(int row, int column) const noexcept;
    void draw();
    void reset();
};
