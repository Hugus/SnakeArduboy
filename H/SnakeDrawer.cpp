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
    //-Serial.println("Draw");
    List< Position > & bones = snake.getBones() ;
    Node< Position > * head = bones.head() ;

    Node< Position > * a = head ;
    Node< Position > * b = head->next() ;

    // Draw line segments
    while ( b != head )
    {
        //-Serial.println("   bone");
        //-Serial.print(a->value()->x);
        //-Serial.print(", ");
        //-Serial.print(a->value()->y);
        //-Serial.print(" -> ");
        //-Serial.print(b->value()->x);
        //-Serial.print(", ");
        //-Serial.println(b->value()->y);
        arduboy.drawLine(a->value()->x, a->value()->y,
                         b->value()->x, b->value()->y,
                         WHITE) ;
        a = b ;
        b = b->next() ;
    }


}
