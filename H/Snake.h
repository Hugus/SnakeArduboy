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
        Snake(Position * pos, unsigned int size, unsigned int width, unsigned int height) ;

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

        private:
        //! Snake movement
        bool move( const Direction direction ) ;

        //! Movement rules
        bool canMove( const Direction direction ) ;

        //! Is there a snake bone at this position
        bool hasBone( const Position & position ) ;

        //! Get movement
        Position getMove( const Direction direction ) ;

        private:
        //! Snake bones
        List< Position > m_bones ;

        //! Space width
        unsigned int m_width ;

        //! Space height
        unsigned int m_height ;

        //! Current direction
        Direction m_currentDirection ;
    } ;
}
#endif
