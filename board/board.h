#pragma once
#include "../matrix/matrix.h"
#include <vector>

struct MatrixPosition
{
    int row;
    int column;
    int step_count;
};

enum class BoardState
{
    NOT_VISITED,
    VISITED
};

enum class TourType
{
    CLOSED,
    OPEN
};

class Vector3D;

class Board
{
private:
    std::vector<MatrixPosition> path;
    const int cell_size = 50;
    const int cube_size = 100;
    TourType tour_type = TourType::CLOSED;
    int knight_starting_row = 0;
    int knight_starting_column = 0;
    const int knight_path_drawing_delay = 60;
    int size = 8;
    int current_index_for_2d_path = 0;
    int current_index_for_3d_path = 0;
    Matrix<BoardState> grid;
    Matrix<int> solution;

    bool is_move_valid(int row, int column) const noexcept;
    bool is_visited(int row, int column) const noexcept;
    bool find_path(int step_count, int row, int column);
    void reset();

public:
    Board();
    void handle_events();
    void resize(int size);
    void toggle_tour_type();
    void find_knights_path();
    int get_size() const noexcept;
    std::vector<int> get_board_pos_regarding_mouse();
    void draw_2d();
    void draw_3d();
    void draw_knights_path_3d();
    void draw_knights_path_2d();
    void draw_mouse_position();
};
