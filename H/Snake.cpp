#include "Snake.h"

#define SPEED 1
#define DELTA_POS 1
#define MARGIN 1 // Walls imply a margin

H::Snake::Snake
(
    Position * pos[],
    unsigned int size,
    unsigned int width,
    unsigned int height
)
: m_isApple( false )
, m_width( width )
, m_height( height )
, m_currentDirection( RIGHT )
, m_hasGrown( false )
, m_grid( width, height )
{
    for ( unsigned int i = 0 ; i < size ; ++i )
    {
        // Initialise node position grid
        m_grid[*pos[i]] = true ;
        // Insert bone
        m_bones.insertFront( pos[i] ) ;
    }
}

//! Destructor
H::Snake::~Snake
(
)
{
    // Delete positions and nodes
    Node< Position > * n = m_bones.head() ;
    Node< Position > * head = m_bones.head() ;
    while ( n->next() !=  head )
    {
        delete n->value() ;
        n = n->next() ;
    }
    // Delete tail
    delete n->value() ;
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
    return false ;
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
    return false ;
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
    return false ;
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
    return false ;
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
    return false ;
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


//! Has grown
bool
H::Snake::hasGrown
(
)
{
    if ( m_hasGrown )
    {
        m_hasGrown = false ;
        return true ;
    }
    return false ;
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

    // Save old tail position
    Position oldTail = *tail->value() ;

    // Take last bone, put it at the front
    *tail->value() = *head->value() + getMove( direction ) ;

    // Update grid there is a bone at this new position
    m_grid[*tail->value()] = true ;

    // Change bones head
    m_bones.setHead( tail );

    // If we just ate an apple, grow
    if ( m_isApple && ( *m_bones.head()->value() == m_apple ) )
    {
        // Hide apple
        hideApple() ;
        // grow
        grow( *m_bones.head()->previous()->value() ) ;
    }
    // If there is no bone left at tail position
    if ( !(*m_bones.head()->previous()->value() == oldTail) )
    {
        // Update grid (there is no more bone at tail position)
        m_grid[oldTail] = false ;
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
            if ( m_bones.head()->value()->y <= 0 )
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
bool
H::Snake::hasBone
(
    const Position & position
)
const
{
    return m_grid[position] ;
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
    m_hasGrown = true ;
}

