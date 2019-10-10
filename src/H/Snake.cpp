#include "Snake.h"

#define DELTA_POS 1

#define COMPRESSOR_FRQ 10
#define PORTAL_FRQ 15

H::Snake::Snake
(
    Position * pos[],
    unsigned int size,
    unsigned int width,
    unsigned int height,
    unsigned int (*random)(unsigned int, unsigned int)
)
: m_isApple( false )
, m_isCompressor( false )
, m_isPortal( false )
, m_width( width )
, m_height( height )
, m_currentDirection( RIGHT )
, m_hasGrown( false )
, m_grid( width, height )
, m_random( random )
, m_appleCount( 0 )
, m_lastCompressor( 0 )
, m_lastPortal( 0 )
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

//! Show apple
bool
H::Snake::showApple
(
)
{
    // Look for an empty spot
    m_apple.x = m_random( 1, m_width ) ;
    m_apple.y = m_random( 1, m_height ) ;
    while( hasBone( m_apple ) )
    {
        m_apple.x = m_random( 1, m_width ) ;
        m_apple.y = m_random( 1, m_height ) ;
    }
    // Spawn an apple
    m_isApple = true ;
    return true ;
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

//! Has compressor ?
bool
H::Snake::hasCompressor
(
)
const
{
    return m_isCompressor ;
}

//! Has compressor ?
bool
H::Snake::hasCompressorAvailable
(
)
const
{
    return m_appleCount >= ( m_lastCompressor + COMPRESSOR_FRQ ) ;
}

//! Where is compressor
const H::Position &
H::Snake::compressor
(
)
const
{
    return m_compressor ;
}

//! Has portal ?
bool
H::Snake::hasPortal
(
)
const
{
    return m_isPortal ;
}

//! Has portal ?
bool
H::Snake::hasPortalAvailable
(
)
const
{
    return m_appleCount >= (m_lastPortal + PORTAL_FRQ) ;
}

//! Where is portal
const H::Position *
H::Snake::portal
(
)
const
{
    return m_portal ;
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

//! Enable a compressor if possible
bool
H::Snake::showCompressor
(
)
{
    if ( hasCompressorAvailable() )
    {
        // If player wait n * COMPRESSOR_FRQ points he has n compressors in reserve
        m_lastCompressor += COMPRESSOR_FRQ ;
        // Look for an empty spot
        m_compressor.x = m_random( 1, m_width ) ;
        m_compressor.y = m_random( 1, m_height ) ;
        while( hasBone( m_compressor ) || ( m_isApple && ( m_apple == m_compressor ) ) )
        {
            m_compressor.x = m_random( 1, m_width ) ;
            m_compressor.y = m_random( 1, m_height ) ;
        }
        // Spawn an compressor
        m_isCompressor = true ;
        return true ;
    }
    return false ;
}

//! Enable portal if possible
bool
H::Snake::showPortal
(
)
{
    if ( hasPortalAvailable() )
    {
        // If player wait n * PORTAL_FRQ points he has n portals in reserve
        m_lastPortal += PORTAL_FRQ ;
        for ( unsigned int i = 0 ; i < 2 ; ++i )
        {
            // Look for an empty spot
            m_portal[i].x = m_random( 1, m_width ) ;
            m_portal[i].y = m_random( 1, m_height ) ;
            while(  hasBone( m_portal[i] ) ||                     // No portal on existing bone
                  ( m_isApple && ( m_apple == m_portal[i] ) ) ||  // Nor on apple
                  ( ( i == 1 ) && m_portal[1] == m_portal[0] )    // Nor on other side of portal
                 )
            {
                m_portal[i].x = m_random( 1, m_width ) ;
                m_portal[i].y = m_random( 1, m_height ) ;
            }
        }
        // Spawn an portal
        m_isPortal = true ;
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
        // Count apple
        ++m_appleCount ;
        // grow
        grow( *m_bones.head()->previous()->value() ) ;
    }
    // If there is no bone left at tail position
    if ( !(*m_bones.head()->previous()->value() == oldTail) )
    {
        // Update grid (there is no more bone at tail position)
        m_grid[oldTail] = false ;
    }

    // If we entered a compressor
    if ( m_isCompressor && ( *m_bones.head()->value() == m_compressor ) )
    {
        // Set all bones at compressor location
        Node< Position > * n = m_bones.head() ;
        const Node< Position > * head = m_bones.head() ;
        while( n->next() != head )
        {
            m_grid[*n->value()] = false ;
            *n->value() = m_compressor ;
            n = n->next() ;
        }
        m_grid[*n->value()] = false ;
        *n->value() = m_compressor ;

        // Only bone position
        m_grid[m_compressor] = true ;

        // Hide compressor
        m_isCompressor = false ;
    }

    // If we entered a portal
    head = m_bones.head() ;
    if ( m_isPortal && ( *head->value() == m_portal[0] ) )
    {
        // Set head at new position
        *head->value() = m_portal[1] ;

        // Update grid
        m_grid[m_portal[1]] = true ;
        m_grid[m_portal[0]] = false ;

        // Hide portal
        m_isPortal = false ;
    }
    else if (m_isPortal && ( *head->value() == m_portal[1] ) )
    {
        // Set head at new position
        *head->value() = m_portal[0] ;

        // Update grid
        m_grid[m_portal[0]] = true ;
        m_grid[m_portal[1]] = false ;

        // Hide portal
        m_isPortal = false ;
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

