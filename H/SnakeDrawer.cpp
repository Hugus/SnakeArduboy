#include "SnakeDrawer.h"
#include "List.h"
#include "Position.h"
#include "Snake.h"

#include <Arduboy.h>
#define DRAW_FACTOR 2
#define DRAW_FACTOR_2 2

void
H::SnakeDrawer::Draw
(
    Snake & snake,
    Arduboy & arduboy
)
{
    List< Position > & bones = snake.getBones() ;
    Node< Position > * head = bones.head() ;

    Node< Position > * a = head ;
    Node< Position > * b = head->next() ;

    // Draw line segments
    while ( b != head )
    {
        arduboy.fillRect(DRAW_FACTOR * a->value()->x , DRAW_FACTOR * a->value()->y ,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
        a = b ;
        b = b->next() ;
    }

    // Draw apple
    if ( snake.hasApple() )
    {
        arduboy.fillRect(DRAW_FACTOR * snake.apple().x , DRAW_FACTOR * snake.apple().y ,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
    }

    // Draw walls
    arduboy.drawFastHLine( 1, 1, snake.getWidth() * DRAW_FACTOR, WHITE ) ;
    arduboy.drawFastHLine( 1, snake.getHeight()* DRAW_FACTOR, snake.getWidth()* DRAW_FACTOR, WHITE ) ;

    arduboy.drawFastVLine( 1, 1, snake.getHeight()* DRAW_FACTOR, WHITE ) ;
    arduboy.drawFastVLine( snake.getWidth()* DRAW_FACTOR, 1, snake.getHeight() * DRAW_FACTOR , WHITE ) ;
}
