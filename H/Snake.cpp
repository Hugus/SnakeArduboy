#include "Snake.h"

#define SPEED 1
#define DELTA_POS 1

H::Snake::Snake
(
    Position * pos,
    unsigned int size,
    unsigned int width,
    unsigned int height
)
: m_width( width )
, m_height( height )
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

//! Snake movement
bool
H::Snake::up
(
)
{
    // If movement is possible
    if ( m_bones.head()->value()->y <= 0 )
    {
        return false ;
    }
    return move( UP ) ;
}

//! Snake movement
bool
H::Snake::down
(
)
{
    // If movement is possible
    if ( m_bones.head()->value()->y >= m_height )
    {
        return false ;
    }
    return move( DOWN ) ;
}

//! Snake movement
bool
H::Snake::right
(
)
{
    // If movement is possible
    if ( m_bones.head()->value()->x >= m_width )
    {
        return false ;
    }
    return move( RIGHT ) ;
}

//! Snake movement
bool
H::Snake::left
(
)
{
    // If movement is possible
    if ( m_bones.head()->value()->x <= 0 )
    {
        return false ;
    }
    return move( LEFT ) ;
}

bool
H::Snake::move
(
    const Direction direction
)
{
    Node< Position > * head = m_bones.head() ;
    Node< Position > * tail = m_bones.head()->previous() ;

    // Take last bone, put it at the front
    switch ( direction )
    {
        case UP:
            tail->value()->x = head->value()->x ;
            tail->value()->y = head->value()->y - DELTA_POS ;
            break;
        case DOWN:
            tail->value()->x = head->value()->x ;
            tail->value()->y = head->value()->y + DELTA_POS ;
            break;
        case RIGHT:
            tail->value()->x = head->value()->x + DELTA_POS ;
            tail->value()->y = head->value()->y ;
            break;
        case LEFT:
            tail->value()->x = head->value()->x - DELTA_POS ;
            tail->value()->y = head->value()->y ;
            break;
    }

    // Change bones head
    m_bones.setHead( tail );

    return true ;
}
