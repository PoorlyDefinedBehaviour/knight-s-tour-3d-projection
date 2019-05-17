#include "board.h"
#include "../sdlcontroller/sdlcontroller.h"

Board::Board()
{
    this->matrix.resize(this->size, this->size);
}

void Board::resize(int size)
{
    this->matrix.resize(size, size);

    this->size = size;
    this->cell_width = SDLController::WINDOW_WIDTH / this->size;
    this->cell_height = SDLController::WINDOW_HEIGHT / this->size;

    this->reset();
}

void Board::reset()
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            this->matrix.elements[i][j] = Cell();
        }
    }
}

int Board::get_size() const noexcept
{
    return this->size;
}

int Board::get_cell_width() const noexcept
{
    return this->cell_width;
}

int Board::get_cell_height() const noexcept
{
    return this->cell_height;
}

void Board::visit(int row, int column)
{
    this->matrix.elements[row][column].visited = true;
}

void Board::unvisit(int row, int column)
{
    this->matrix.elements[row][column].visited = false;
}

bool Board::is_visited(int row, int column) const noexcept
{
    return this->matrix.elements[row][column].visited;
}

void Board::draw()
{
    /*
     * light blue = rgb(106, 137, 204)
     * red = rgb(198, 40, 40)
     * */
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            if ((i + j) % 2 == 0)
            {
                SDLController::set_color(255, 255, 255);
            }
            else
            {
                SDLController::set_color(106, 137, 204);
            }

            SDLController::render_rectangle(this->cell_width,
                                            this->cell_height,
                                            i * this->cell_width,
                                            j * this->cell_height);
        }
    }
}
