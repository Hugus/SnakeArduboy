#include "SnakeDrawer.h"
#include "List.h"
#include "Position.h"
#include "Snake.h"

#include <Arduboy.h>

#define DRAW_FACTOR 4
#define DRAW_FACTOR_2 2
#define DRAW_MARGIN 1

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

    // Draw line segments
    while ( a->next() != head )
    {
        arduboy.fillRect(DRAW_FACTOR * a->value()->x - DRAW_MARGIN, DRAW_FACTOR * a->value()->y + DRAW_MARGIN,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
        a = a->next() ;
    }
        arduboy.fillRect(DRAW_FACTOR * a->value()->x - DRAW_MARGIN, DRAW_FACTOR * a->value()->y + DRAW_MARGIN,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;

    // Draw apple
    if ( snake.hasApple() )
    {
        arduboy.fillRect(DRAW_FACTOR * snake.apple().x -DRAW_MARGIN, DRAW_FACTOR * snake.apple().y +DRAW_MARGIN,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
    }

    // Draw walls
    arduboy.drawFastHLine( 2, 0, snake.getWidth() * DRAW_FACTOR - 2 * DRAW_MARGIN, WHITE ) ;
    arduboy.drawFastHLine( 2, snake.getHeight()* DRAW_FACTOR + DRAW_MARGIN, snake.getWidth() * DRAW_FACTOR - 2 * DRAW_MARGIN, WHITE ) ;

    arduboy.drawFastVLine( 2, 0, snake.getHeight()* DRAW_FACTOR +DRAW_MARGIN, WHITE ) ;
    arduboy.drawFastVLine( snake.getWidth()* DRAW_FACTOR - DRAW_MARGIN, DRAW_MARGIN, snake.getHeight() * DRAW_FACTOR , WHITE ) ;

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
