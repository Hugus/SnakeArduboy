#ifndef SNAKE_DRAWER_H
#define SNAKE_DRAWER_H

//! Forward declaration
class Arduboy2 ;

namespace H
{
    //! Forward declaration
    class Snake ;

    //! Snake drawing facilities
    class SnakeDrawer
    {
        public:
        static void Draw( Snake & snake, Arduboy2 & arduboy, unsigned int score, unsigned int maxScore ) ;
    } ;
}
#endif
