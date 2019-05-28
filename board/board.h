#pragma once
#include "../matrix/matrix.h"
#include <vector>
#include <array>
#include <map>
#include <thread>
#include <mutex>

class Vector3D;

class Board
{
private:
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

    std::mutex knights_tour_thread_mutex;
    std::vector<std::pair<int, int>> moves = { std::make_pair(-2, 1),
                                               std::make_pair(-1, 2),
                                               std::make_pair(1, 2),
                                               std::make_pair(2, 1),
                                               std::make_pair(2, -1),
                                               std::make_pair(1, -2),
                                               std::make_pair(-1, -2),
                                               std::make_pair(-2, -1) };
    std::vector<MatrixPosition> path;
    Matrix<BoardState> grid;

    int size = 8;
    int cell_size = 50;
    int knight_starting_row = 0;
    int knight_starting_column = 0;

    int path_drawing_delay = 60;
    size_t current_drawing_index = 0;
    int board3d_starting_position_x = 0;
    int board3d_starting_position_y = 0;

    int get_num_neighbours(int row, int column);
    bool is_move_valid(int row, int column);
    bool is_visited(size_t row, size_t column);
    bool find_path(int step_count, int row, int column);
    void draw_knights_path_3d();
    void draw_knights_path_2d();
    void draw_2d();
    void draw_3d();
    void reset();

    std::pair<int, int> get_board_pos_regarding_mouse();
    std::multimap<int, std::pair<int, int>> get_ordered_moves(int current_row, int current_column);

public:
    Board();
    void handle_events();
    void resize(int size);
    void find_knights_path();

    void set_path_drawing_delay(int delay);
    int get_path_drawing_delay() const;
    int get_size() const noexcept;

    void draw();
    void draw_paths();
    void draw_mouse_position();
};
