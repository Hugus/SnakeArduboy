#include "SnakeDrawer.h"
#include "List.h"
#include "Position.h"
#include "Snake.h"

#include <Arduboy.h>

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
        arduboy.drawLine(a->value()->x, a->value()->y,
                         b->value()->x, b->value()->y,
                         WHITE) ;
        a = b ;
        b = b->next() ;
    }


}
