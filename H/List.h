#ifndef LIST_H
#define LIST_H

#include <stddef.h>

namespace H
{
    //! Liste node class
    template< typename _T >
    class Node
    {
        public:
        Node
        (
            _T * value
        )
        : m_value( value )
        , m_previous( NULL )
        , m_next( NULL )
        {
        }

        //! Cast operator to node element type
        operator _T*() { return m_value ; }

        //! Value getter
        _T * value() { return m_value ; }

        //! Get next node
        Node< _T > * next() const ;
        //! Get previous node
        Node< _T > * previous() const ;

        //! Set next node
        void setNext( Node< _T > * n ) ;
        //! Set previous node
        void setPrevious( Node< _T > * n ) ;

        private:
        //! Pointer to previous node
        Node * m_previous ;
        //! Pointer to next node
        Node * m_next ;
        //! Stored value
        _T * m_value ;
    } ;

    //! Double linked list of NodeType
    template< typename NodeType >
    class List
    {
        public:
        List() {}

        //! Set list head
        void setHead( Node< NodeType > * head ) ;
        //! Get head ;)
        Node< NodeType > * head() ;
        //! Insert in first position
        void insertFront( NodeType * element ) ;
        //! Insert at end of list
        void insertBack( NodeType * element ) ;
        //! Get first element
        const NodeType * first() const ;
        //! Get last element
        const NodeType * last() const ;
        //! Get list size (N complexity)
        unsigned int size() const ;

        private:
        //! List head
        Node< NodeType > * m_head ;
    } ;


    // -------------------------------------------------------------------------
    // Node implementation
    // -------------------------------------------------------------------------

    //! Get next node
    template< typename _T >
    Node< _T > *
    Node< _T >::next
    (
    )
    const
    {
        return m_next ;
    }

    //! Get previous node
    template< typename _T >
    Node< _T > *
    Node< _T >::previous
    (
    )
    const
    {
        return m_previous ;
    }

    //! Set next node
    template< typename _T >
    void
    Node< _T >::setNext
    (
        Node< _T > * n
    )
    {
        m_next = n ;
    }

    //! Set previous node
    template< typename _T >
    void
    Node< _T >::setPrevious
    (
        Node< _T > * n
    )
    {
        m_previous = n ;
    }

    // -------------------------------------------------------------------------
    // List implementation
    // -------------------------------------------------------------------------

    //! Set list head
    template< typename NodeType >
    void
    List< NodeType >::setHead
    (
        Node< NodeType > * head
    )
    {
        m_head = head ;
    }

    //! Get head ;)
    template< typename NodeType >
    Node< NodeType > *
    List< NodeType >::head
    (
    )
    {
        return m_head ;
    }

    //! Insert in first position
    template< typename NodeType >
    void
    List< NodeType >::insertFront
    (
        NodeType * element
    )
    {
        // Create node
        Node< NodeType > * n = new Node< NodeType >( element ) ;
        if ( m_head != NULL )
        {
            n->setNext( m_head ) ;
            n->setPrevious( m_head->previous() ) ;
            m_head->previous()->setNext( n ) ;
            m_head->setPrevious( n ) ;
            m_head = n ;
        }
        else
        {
            // Empty list
            m_head = n ;
            m_head->setPrevious( m_head ) ;
            m_head->setNext( m_head ) ;
        }
    }

    //! Insert at end of list
    template< typename NodeType >
    void
    List< NodeType >::insertBack
    (
        NodeType * element
    )
    {
        throw "Todo implement" ;
    }

    //! Get first element
    template< typename NodeType >
    const NodeType *
    List< NodeType >::first
    (
    )
    const
    {
        // Cast from Node< NodeType > to NodeType*
        return m_head ;
    }

    //! Get last element
    template< typename NodeType >
    const NodeType *
    List< NodeType >::last
    (
    )
    const
    {
        // Cast from Node< NodeType > to NodeType*
        return m_head->previous() ;
    }

    //! Get list size (N complexity)
    template< typename NodeType >
    unsigned int
    List< NodeType >::size
    (
    )
    const
    {
        if ( m_head == NULL )
        {
            return 0 ;
        }

        unsigned int i = 1 ;
        const Node< NodeType > * current = m_head->next() ;
        while ( current != m_head )
        {
            current = current->next() ;
            ++i ;
        }
        return i ;
    }
}

#endif
