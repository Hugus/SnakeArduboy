#include "SnakeDrawer.h"
#include "List.h"
#include "Position.h"
#include "Snake.h"

#include <Arduboy.h>
#define DRAW_FACTOR 4
#define DRAW_FACTOR_2 2

void
H::SnakeDrawer::Draw
(
    Snake & snake,
    Arduboy & arduboy,
    unsigned int score,
    unsigned int maxScore
)
{
    List< Position > & bones = snake.getBones() ;
    Node< Position > * head = bones.head() ;

    Node< Position > * a = head ;
    Node< Position > * b = head->next() ;

    // Draw line segments
    while ( b != head )
    {
        arduboy.fillRect(DRAW_FACTOR * a->value()->x - 1, DRAW_FACTOR * a->value()->y + 1,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
        a = b ;
        b = b->next() ;
    }

    // Draw apple
    if ( snake.hasApple() )
    {
        arduboy.fillRect(DRAW_FACTOR * snake.apple().x -1, DRAW_FACTOR * snake.apple().y +1,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
    }

    // Draw walls
    arduboy.drawFastHLine( 1, 0, snake.getWidth() * DRAW_FACTOR, WHITE ) ;
    arduboy.drawFastHLine( 1, snake.getHeight()* DRAW_FACTOR + 1, snake.getWidth()* DRAW_FACTOR, WHITE ) ;

    arduboy.drawFastVLine( 1, 0, snake.getHeight()* DRAW_FACTOR +1, WHITE ) ;
    arduboy.drawFastVLine( snake.getWidth()* DRAW_FACTOR, 1, snake.getHeight() * DRAW_FACTOR , WHITE ) ;

    // Draw score
    arduboy.setCursor( 65, 10 ) ;
    arduboy.print("Score : ") ;
    arduboy.setCursor( 110, 10 ) ;
    arduboy.print(score) ;
    arduboy.setCursor( 65, 20 ) ;
    arduboy.print("Max   : ") ;
    arduboy.setCursor( 110, 20 ) ;
    arduboy.print(maxScore) ;

}
