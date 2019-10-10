#include "Position.h"

H::Position
H::operator +
(
    const H::Position & left,
    const H::Position & right
)
{
    return Position( left.x + right.x, left.y + right.y ) ;
}

bool
H::operator ==
(
    const H::Position & left,
    const H::Position & right
)
{
    return left.x == right.x &&
        left.y == right.y ;
}


H::Grid::Grid
(
    unsigned int width,
    unsigned int height
)
: width( width )
{
    grid = new bool[width*height]() ;
}

H::Grid::~Grid
(
)
{
    delete[] grid ;
}

bool &
H::Grid::operator []
(
    const Position & position
)
{
    return grid[position.y * width + position.x] ;
}

bool
H::Grid::operator []
(
    const Position & position
)
const
{
    return grid[position.y * width + position.x] ;
}

