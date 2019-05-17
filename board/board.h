#pragma once
#include "../cell/cell.h"
#include "../matrix/matrix.h"

class Board
{
private:
    int size = 7;
    Matrix<Cell> matrix;
    int cell_width;
    int cell_height;

public:
    Board();
    void resize(int size);
    int get_size() const noexcept;
    int get_cell_width() const noexcept;
    int get_cell_height() const noexcept;
    void visit(int row, int column);
    void unvisit(int row, int column);
    bool is_visited(int row, int column) const noexcept;
    void draw();
    void reset();
};
