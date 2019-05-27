#include "board.h"
#include "../sdlcontroller/sdlcontroller.h"
#include "../vector/vector.h"
#include <algorithm>

Board::Board()
{
    this->grid.resize(this->size, this->size);
}

void Board::handle_events()
{
    const int board_position_change_speed = 10;
    Uint8 *keysArray = const_cast<Uint8 *>(SDL_GetKeyboardState(nullptr));

    if (SDLController::event_handler.type == SDL_MOUSEBUTTONDOWN &&
            SDLController::event_handler.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        SDL_PollEvent(&SDLController::event_handler);
        SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
        SDL_PumpEvents();

        auto position = this->get_board_pos_regarding_mouse();
        const int &row = position.first;
        const int &column = position.second;

        if (row != -1 && column != -1)
        {
            this->knight_starting_row = row;
            this->knight_starting_column = column;
            this->reset();
        }
    }

    if (keysArray[SDL_SCANCODE_W])
    {
        this->board3d_starting_position_y += (-board_position_change_speed);
    }

    if (keysArray[SDL_SCANCODE_S])
    {
        this->board3d_starting_position_y += (board_position_change_speed);
    }

    if (keysArray[SDL_SCANCODE_A])
    {
        this->board3d_starting_position_x += (-board_position_change_speed);
    }

    if (keysArray[SDL_SCANCODE_D])
    {
        this->board3d_starting_position_x += board_position_change_speed;
    }
}

void Board::resize(int size)
{
    if (size < 3 || this->size == size)
        return;

    this->size = size;
    this->cell_size = 500 / this->size;
    this->cube_size = 500 / this->size;
    this->knight_starting_row = this->knight_starting_column = 0;
    this->reset();
    std::cout << "New board size: " << this->size << " x " << this->size << '\n';
}

void Board::set_path_drawing_delay(int delay){
    this->path_drawing_delay = delay;
    std::cout << "New path drawing delay: " << this->path_drawing_delay << '\n';
}

int Board::get_path_drawing_delay() const {
    return this->path_drawing_delay;
}

void Board::reset()
{
    this->grid.resize(size, size);
    this->grid.fill([&]() { return BoardState::NOT_VISITED; });
    this->path.clear();
    this->current_index_for_2d_path = this->current_index_for_3d_path =  0;
}

bool Board::is_visited(int row, int column)
{
    return grid[row][column] != BoardState::NOT_VISITED;
}

void Board::draw_2d()
{
    for (auto i = 0; i < this->size; ++i)
    {
        for (auto j = 0; j < this->size; ++j)
        {
            if ((i + j) % 2 == 0)
            {
                SDLController::set_color(255, 255, 255);
            }
            else
            {
                SDLController::set_color(106, 137, 204);
            }

            SDLController::render_rectangle(SDLController::WINDOW_WIDTH / 2 + i * this->cell_size,
                                            100 + j * this->cell_size,
                                            this->cell_size,
                                            this->cell_size);
        }
    }
}

void Board::draw_3d()
{
    SDLController::set_color(46, 125, 50);
    for (auto i = 0; i < this->grid.get_rows(); ++i)
    {
        for (auto j = 0; j < this->grid.get_columns(); ++j)
        {
            SDLController::render_cube(this->board3d_starting_position_x + i * this->cube_size,
                                       this->board3d_starting_position_y + j * this->cube_size,
                                       0,
                                       this->cube_size);
        }
    }
}

void Board::draw_knights_path_2d()
{
    static int time_passed = 0;
    std::vector<SDL_Point> points;

    SDLController::set_color(255, 0, 0);
    SDLController::render_rectangle(SDLController::WINDOW_HALF_WIDTH + this->knight_starting_row * this->cell_size,
                                    100 + this->knight_starting_column * this->cell_size,
                                    this->cell_size,
                                    this->cell_size);

    for (size_t i = 0; i < this->path.size(); ++i)
    {
        points.push_back({(SDLController::WINDOW_WIDTH / 2 + this->path[i].row * this->cell_size) + cell_size / 2,
                          100 + (this->path[i].column * cell_size) + cell_size / 2});

        if(i > this->current_index_for_2d_path)
            break;
    }

    if (++time_passed > this->path_drawing_delay)
    {
        time_passed = 0;

        if (++current_index_for_2d_path > this->path.size())
        {
            current_index_for_2d_path = 0;
            this->path.clear();
        }
    }

    for (auto i = 0; i < current_index_for_2d_path; ++i)
    {
        auto current_cell = this->path[i];

        SDLController::set_color(198, 40, 40);
        SDLController::render_rectangle(SDLController::WINDOW_HALF_WIDTH + current_cell.row * this->cell_size,
                                        100 + current_cell.column * this->cell_size,
                                        this->cell_size,
                                        this->cell_size);
    }

    SDLController::set_color(46, 125, 50);
    SDLController::render_lines(&points[0], current_index_for_2d_path);
}

void Board::draw_knights_path_3d()
{
    static int time_passed = 0;

    if (++time_passed >= this->path_drawing_delay)
    {
        time_passed = 0;

        if (++current_index_for_3d_path > this->path.size())
            current_index_for_3d_path = 0;
    }

    SDLController::set_color(255, 0, 0);
    for (auto i = 0; i < this->current_index_for_3d_path; ++i)
    {
        SDLController::render_cube(this->board3d_starting_position_x + this->path[i].row * this->cube_size,
                                   this->board3d_starting_position_y + this->path[i].column * this->cube_size,
                                   300,
                                   this->cube_size);
    }
}

void Board::draw_mouse_position()
{
    auto position = this->get_board_pos_regarding_mouse();

    if (position.first == -1 || position.second == -1)
        return;

    const int &row = position.first;
    const int &column = position.second;

    SDLController::render_rectangle(SDLController::WINDOW_HALF_WIDTH + row * this->cell_size,
                                    100 + column * this->cell_size,
                                    this->cell_size,
                                    this->cell_size);
}

void Board::find_knights_path()
{
    this->knights_tour_thread_mutex.lock();
    this->reset();
    this->knights_tour_thread_mutex.unlock();

    this->knights_tour_thread_mutex.lock();
    this->grid[this->knight_starting_row][this->knight_starting_column] = BoardState::VISITED;
    this->knights_tour_thread_mutex.unlock();

    std::cout << "Searching..." << '\n';
    std::cout << "Minimum steps: "
              << this->size * this->size
              << " -> "
              << (!this->find_path(1, this->knight_starting_row, this->knight_starting_column) ? "No solution found..." : "Solution found!")
              << '\n';

    std::sort(this->path.begin(),
              this->path.end(),
              [](const auto &lhs, const auto &rhs) -> bool {
        return lhs.step_count < rhs.step_count;
    });
}

bool Board::find_path(int step_count, int row, int column)
{
    this->knights_tour_thread_mutex.lock();
    if (step_count == this->size * this->size)
    {
        this->knights_tour_thread_mutex.unlock();
        return true;
    }
    this->knights_tour_thread_mutex.unlock();

    this->knights_tour_thread_mutex.lock();
    auto ordered_moves = get_ordered_moves(row, column);
    this->knights_tour_thread_mutex.unlock();

    for (const auto &move : ordered_moves)
    {
        const int next_row = row + move.second.first;
        const int next_column = column + move.second.second;

        if (is_move_valid(next_row, next_column))
        {
            this->knights_tour_thread_mutex.lock();
            this->grid[next_row][next_column] = BoardState::VISITED;
            this->knights_tour_thread_mutex.unlock();

            if (find_path(step_count + 1, next_row, next_column))
            {
                this->knights_tour_thread_mutex.lock();
                this->path.push_back({next_row, next_column, step_count});
                this->knights_tour_thread_mutex.unlock();
                return true;
            }

            this->knights_tour_thread_mutex.lock();
            this->grid[next_row][next_column] = BoardState::NOT_VISITED;
            this->knights_tour_thread_mutex.unlock();
        }
    }

    SDLController::handle_events();
    this->knights_tour_thread_mutex.unlock();
    return false;
}

std::multimap<int, std::pair<int, int>> Board::get_ordered_moves(int current_row, int current_column)
{
    std::multimap<int, std::pair<int, int>> ordered_moves;

    for (const auto &move : this->moves)
    {
        const int next_row = current_row + move.first;
        const int next_column = current_column + move.second;

        if (is_move_valid(next_row, next_column))
        {
            ordered_moves.insert(std::make_pair(get_num_neighbours(next_row, next_column), move));
        }
    }

    return ordered_moves;
}

int Board::get_num_neighbours(int row, int column)
{
    int neighbours = 0;

    for (const auto &move : this->moves)
    {
        const int next_row = row + move.first;
        const int next_column = column + move.second;

        if (is_move_valid(next_row, next_column))
        {
            ++neighbours;
        }
    }

    return neighbours;
}

bool Board::is_move_valid(int row, int column)
{
    return row >= 0 &&
            column >= 0 &&
            row < this->size &&
            column < this->size &&
            this->grid[row][column] == BoardState::NOT_VISITED;
}

int Board::get_size() const noexcept
{
    return this->size;
}

std::pair<int, int> Board::get_board_pos_regarding_mouse()
{
    auto mouse_pos = SDLController::get_mouse_position();
    const int &x = mouse_pos.first;
    const int &y = mouse_pos.second;

    if (x < SDLController::WINDOW_HALF_WIDTH || y < 100 ||
            x > (SDLController::WINDOW_HALF_WIDTH + this->size * this->cell_size) || y > (100 + this->size * this->cell_size))
    {
        return {-1, -1};
    }

    const int row = (x - SDLController::WINDOW_HALF_WIDTH) / this->cell_size;
    const int column = (y - 100) / this->cell_size;

    return std::make_pair(row, column);
}
