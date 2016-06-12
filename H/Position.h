#ifndef POSITION_H
#define POSITION_H

namespace H
{
    typedef unsigned short Coord ;
    struct Position
    {
        Position()
        : x( 0 )
        , y( 0 )
        {
        }

        Position( Coord x, Coord y )
        : x( x )
        , y( y )
        {
        }

        Coord x ;
        Coord y ;
    } ;

    Position operator + ( const Position & left, const Position & right ) ;

    bool operator == ( const Position & left, const Position & right ) ;
}

#endif
