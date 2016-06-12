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
: m_isApple( false )
, m_width( width )
, m_height( height )
, m_currentDirection( RIGHT )
{
    for ( unsigned int i = 0 ; i < size ; ++i )
    {
        m_bones.insertFront( &pos[i] ) ;
    }
}


//! Get space dimension
unsigned int
H::Snake::getWidth
(
)
{
    return m_width ;
}

//! Get space dimension
unsigned int
H::Snake::getHeight
(
)
{
    return m_height ;
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
    if ( canMove( UP ) )
    {
        return move( UP ) ;
    }
}

//! Snake movement
bool
H::Snake::down
(
)
{
    // If movement is possible
    if ( canMove( DOWN ) )
    {
        return move( DOWN ) ;
    }
}

//! Snake movement
bool
H::Snake::right
(
)
{
    // If movement is possible
    if ( canMove( RIGHT ) )
    {
        return move( RIGHT ) ;
    }
}

//! Snake movement
bool
H::Snake::left
(
)
{
    // If movement is possible
    if ( canMove( LEFT ) )
    {
        return move( LEFT ) ;
    }
}

//! Continue moving
bool
H::Snake::keepGoing
(
)
{
    // If movement is possible
    if ( canMove( m_currentDirection ) )
    {
        return move( m_currentDirection ) ;
    }
}

//! Hide apple
void
H::Snake::hideApple
(
)
{
    m_isApple = false ;
}

//! Has apple ?
bool
H::Snake::hasApple
(
)
const
{
    return m_isApple ;
}

//! Where is apple
const H::Position &
H::Snake::apple
(
)
const
{
    return m_apple ;
}

bool
H::Snake::move
(
    const Direction direction
)
{
    m_currentDirection = direction ;

    Node< Position > * head = m_bones.head() ;
    Node< Position > * tail = m_bones.head()->previous() ;

    Position oldTail = *tail->value() ;

    // Take last bone, put it at the front
    *tail->value() = *head->value() + getMove( direction ) ;

    // Change bones head
    m_bones.setHead( tail );

    // If we just ate an apple, grow
    if ( m_isApple && ( *m_bones.head()->value() == m_apple ) )
    {
        // Hide apple
        hideApple() ;
        // grow
        grow( oldTail ) ;
    }

    return true ;
}

//! Movement rules
bool
H::Snake::canMove
(
    const Direction direction
)
{
    // First test walls, then bones
    switch ( direction )
    {
        case UP:
            if ( m_bones.head()->value()->y <= DELTA_POS )
            {
                return false ;
            }
            break;
        case DOWN:
            if ( m_bones.head()->value()->y >= m_height - DELTA_POS )
            {
                return false ;
            }
            break;
        case RIGHT:
            if ( m_bones.head()->value()->x >= m_width - DELTA_POS )
            {
                return false ;
            }
            break;
        case LEFT:
            if ( m_bones.head()->value()->x <= DELTA_POS )
            {
                return false ;
            }
            break;
    }
    // Test bones
    if ( hasBone( *m_bones.head()->value() + getMove( direction ) ) )
    {
        return false ;
    }
    return true ;
}

//! Is there a snake bone at this position
//! TODO, catastrophic complexity
bool
H::Snake::hasBone
(
    const Position & position
)
{
    // Iterate over bones
    Node< Position > * head = m_bones.head() ;
    if ( *head->value() == position )
    {
        return true ;
    }
    Node< Position > * n = head->next() ;
    while ( n != head )
    {
        if ( *n->value() == position )
        {
            return true ;
        }
        n = n->next() ;
    }
    return false ;
}

//! Get movement
H::Position
H::Snake::getMove
(
    const Direction direction
)
{
    switch ( direction )
    {
        case UP:
            return Position(0, - DELTA_POS) ;
            break;
        case DOWN:
            return Position(0, DELTA_POS) ;
            break;
        case RIGHT:
            return Position(DELTA_POS, 0) ;
            break;
        case LEFT:
            return Position(-DELTA_POS, 0) ;
            break;
    }
}

//! Grow
void
H::Snake::grow
(
    const Position & oldTail
)
{
    // Add a queue item
    m_bones.insertBack( new Position(oldTail.x, oldTail.y) ) ;
}

