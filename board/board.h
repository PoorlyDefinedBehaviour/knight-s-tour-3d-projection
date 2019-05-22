#pragma once
#include "../matrix/matrix.h"
#include <vector>

struct MatrixPosition
{
    int row;
    int column;
    int step_count;
};

class Vector3D;

class Board
{
private:
    std::vector<MatrixPosition> path;
    const double EMPTY = -1.0;
    const int cell_size = 50;
    const int knight_path_drawing_delay = 60;
    int size = 8;
    int current_index_for_2d_path = 0;
    int current_index_for_3d_path = 0;
    Matrix grid;
    Matrix solution;

    bool is_move_valid(int row, int column);
    bool is_visited(int row, int column) const noexcept;
    bool find_path(int step_count, int row, int column);

public:
    Board();
    void resize(int size);
    void find_knights_path();
    int get_size() const noexcept;
    void draw_2d();
    void draw_3d();
    void draw_knights_path_3d();
    void draw_knights_path_2d();
};
