#ifndef SNAKE_H
#define SNAKE_H

#include "List.h"
#include "Position.h"

// Personal namespace
namespace H
{
    enum Direction
    {
        UP,
        DOWN,
        RIGHT,
        LEFT
    } ;

    class Snake
    {
        public:
        //! Constructor
        //! @param[in] pos position of bones at beginning
        //! @param[in] size snake size at beginning
        Snake(Position * pos[], unsigned int size, unsigned int width, unsigned int height, unsigned int (*random)(unsigned int, unsigned int)) ;

        //! Destructor
        ~Snake() ;

        //! Get space dimension
        unsigned int getWidth() ;
        //! Get space dimension
        unsigned int getHeight() ;

        //! Get snake bones
        List< Position > & getBones() ;

        //! Snake movement
        bool up() ;
        //! Snake movement
        bool down() ;
        //! Snake movement
        bool right() ;
        //! Snake movement
        bool left() ;
        //! Continue moving
        bool keepGoing() ;

        //! Show apple
        bool showApple() ;
        //! Hide apple
        void hideApple() ;

        //! Has apple ?
        bool hasApple() const ;
        //! Where is apple
        const Position & apple() const ;

        //! Has compressor ?
        bool hasCompressor() const ;
        bool hasCompressorAvailable() const ;
        //! Where is compressor
        const Position & compressor() const ;

        //! Has portal ?
        bool hasPortal() const ;
        bool hasPortalAvailable() const ;
        //! Where is portal
        const Position * portal() const ;

        //! Has grown
        bool hasGrown() ;

        //! Enable a compressor if possible
        bool showCompressor() ;

        //! Enable portal
        bool showPortal() ;

        private:
        //! Snake movement
        bool move( const Direction direction ) ;

        //! Movement rules
        bool canMove( const Direction direction ) ;

        //! Is there a snake bone at this position
        bool hasBone( const Position & position ) const ;

        //! Get movement
        Position getMove( const Direction direction ) ;

        //! Grow
        void grow( const Position & oldTail ) ;

        private:
        //! Snake bones
        List< Position > m_bones ;

        //! There can be one apple at a time
        Position m_apple ;
        //! Is apple spawned ?
        bool m_isApple ;

        //! There can be one compressor at a time
        Position m_compressor ;
        //! Is compressor spawned ?
        bool m_isCompressor ;

        //! There can be one portal at a time
        Position m_portal[2] ;
        //! Is portal spawned ?
        bool m_isPortal ;

        //! Space width
        unsigned int m_width ;

        //! Space height
        unsigned int m_height ;

        //! Current direction
        Direction m_currentDirection ;

        //! Has grown
        bool m_hasGrown ;

        //! Bone position bitmap
        Grid m_grid ;

        //! Function pointer to random function
        unsigned int (*m_random)(unsigned int, unsigned int) ;

        //! Apple count
        unsigned int m_appleCount ;

        //! Last compressor (in number of apples)
        unsigned int m_lastCompressor ;

        //! Last portal (in number of apples)
        unsigned int m_lastPortal ;
    } ;
}
#endif
