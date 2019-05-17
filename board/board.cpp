#include "board.h"
#include "../sdlcontroller/sdlcontroller.h"

Board::Board()
{
    this->resize(this->size);
}

Board::~Board()
{
    if (this->elements)
    {
        for (int i = 0; i < this->size; ++i)
            delete[] this->elements[i];
    }
}

void Board::resize(int size)
{
    if (this->elements)
    {
        for (int i = 0; i < this->size; ++i)
            delete[] this->elements[i];
    }

    this->size = size;

    this->elements = new Cell *[this->size];

    for (int i = 0; i < this->size; ++i)
    {
        this->elements[i] = new Cell[this->size];
    }

    this->reset();
}

int Board::get_size() const noexcept
{
    return this->size;
}

void Board::visit(int row, int column)
{
    this->elements[row][column].visited = true;
}

bool Board::is_visited(int row, int column) const noexcept
{
    return this->elements[row][column].visited;
}

void Board::reset()
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            this->elements[i][j] = Cell();
        }
    }
}

void Board::draw()
{
    const int CELL_WIDTH = SDLController::WINDOW_WIDTH / this->size;
    const int CELL_HEIGHT = SDLController::WINDOW_HEIGHT / this->size;

    /*
     * light blue = rgb(106, 137, 204)
     * red = rgb(198, 40, 40)
     * */
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {

            if (this->elements[i][j].visited)
            {
                SDLController::setRendererColor(198, 40, 40);
            }
            else if ((i + j) % 2 == 0)
            {
                SDLController::setRendererColor(255, 255, 255);
            }
            else
            {
                SDLController::setRendererColor(106, 137, 204);
            }

            SDLController::renderRectangle(CELL_WIDTH,
                                           CELL_HEIGHT,
                                           i * CELL_WIDTH,
                                           j * CELL_HEIGHT);
        }
    }
}
