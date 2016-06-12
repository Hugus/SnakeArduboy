#ifndef SNAKE_H
#define SNAKE_H

#include "List.h"
#include "Position.h"

// Personal namespace
namespace H
{
    class Snake
    {
        public:
        //! Constructor
        //! @param[in] pos position of bones at beginning
        //! @param[in] size snake size at beginning
        Snake(Position * pos, unsigned int size) ;

        //! Get snake bones
        List< Position > & getBones() ;

        private:
        //! Snake bones
        List< Position > m_bones ;
    } ;
}
#endif
