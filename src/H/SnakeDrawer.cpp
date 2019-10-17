#include "SnakeDrawer.h"
#include "List.h"
#include "Position.h"
#include "Snake.h"

#include <Arduboy2.h>

#define DRAW_FACTOR 4
#define DRAW_FACTOR_2 2
#define DRAW_MARGIN 1

void
H::SnakeDrawer::Draw
(
    Snake & snake,
    Arduboy2 & arduboy,
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


    // Draw compressor
    if ( snake.hasCompressor() )
    {
        arduboy.drawRect(DRAW_FACTOR * snake.compressor().x -DRAW_MARGIN, DRAW_FACTOR * snake.compressor().y +DRAW_MARGIN,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
    }

    // Draw portal
    if ( snake.hasPortal() )
    {

        arduboy.drawRoundRect(DRAW_FACTOR * snake.portal()[0].x -DRAW_MARGIN, DRAW_FACTOR * snake.portal()[0].y +DRAW_MARGIN,
                         DRAW_FACTOR, DRAW_FACTOR,
                         DRAW_FACTOR_2,
                         WHITE) ;
        arduboy.drawRoundRect(DRAW_FACTOR * snake.portal()[1].x -DRAW_MARGIN, DRAW_FACTOR * snake.portal()[1].y +DRAW_MARGIN,
                         DRAW_FACTOR, DRAW_FACTOR,
                         DRAW_FACTOR_2,
                         WHITE) ;
    }

    // Draw walls
    arduboy.drawFastHLine( 2, 0, snake.getWidth() * DRAW_FACTOR - 2 * DRAW_MARGIN, WHITE ) ;
    arduboy.drawFastHLine( 2, snake.getHeight()* DRAW_FACTOR + DRAW_MARGIN, snake.getWidth() * DRAW_FACTOR - 2 * DRAW_MARGIN, WHITE ) ;

    arduboy.drawFastVLine( 2, 0, snake.getHeight()* DRAW_FACTOR +DRAW_MARGIN, WHITE ) ;
    arduboy.drawFastVLine( snake.getWidth()* DRAW_FACTOR - DRAW_MARGIN, DRAW_MARGIN, snake.getHeight() * DRAW_FACTOR , WHITE ) ;

    // Draw score
    arduboy.setCursor( 5, 56 ) ;
    arduboy.print("Score") ;
    arduboy.setCursor( 38, 56 ) ;
    arduboy.print(score) ;
    arduboy.setCursor( 55, 56 ) ;
    arduboy.print("Max") ;
    arduboy.setCursor( 75, 56 ) ;
    arduboy.print(maxScore) ;

    // Draw info about portal or compressor
    if ( snake.hasCompressorAvailable() )
    {
        arduboy.drawRect( 100 , 56,
                         DRAW_FACTOR, DRAW_FACTOR,
                         WHITE) ;
    }
    // Draw info about portal or compressor
    if ( snake.hasPortalAvailable() )
    {
        arduboy.drawRoundRect( 108 , 56,
                         DRAW_FACTOR, DRAW_FACTOR,
                         DRAW_FACTOR_2,
                         WHITE) ;
    }


}
