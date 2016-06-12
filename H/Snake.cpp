#include "Snake.h"

H::Snake::Snake
(
    Position * pos,
    unsigned int size
)
{
    for ( unsigned int i = 0 ; i < size ; ++i )
    {
        m_bones.insertFront( &pos[size - i - 1] ) ;
    }
}

//! Get snake bones
H::List< H::Position > &
H::Snake::getBones
(
)
{
    return m_bones ;
}

