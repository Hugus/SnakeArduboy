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
