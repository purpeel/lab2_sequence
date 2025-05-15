#ifndef LISTSEQ_H
#define LISTSEQ_H

#include "Sequence.hpp"
#include "LinkedList.hpp"

template <typename T>
class ListSequence : public Sequence<T>
{
public:
    ListSequence();
    ListSequence( const int size );

    ListSequence( const LinkedList<T>& src );
    ListSequence<T> operator=( const ListSequence<T>& src );

    ListSequence( LinkedList<T>&& src );
    ListSequence<T> operator=( LinkedList<T>&& src );
public:
    void append( const T& value ) override;
    void prepend( const T& value ) override;
    void insertAt( const T& value, const int pos ) override;
    void removeAt( const int pos ) override;
    void setAt( const T& value, const int pos ) override;
    void swap( const int pos1, const int pos2 ) override;
public:
    T& operator[]( const int pos ) override;
    const T& operator[]( const int pos ) const override;
public:
    const bool isEmpty() const override;
    const int getSize() const override;
private:
    LinkedList<T> list;
}

#endif //LISTSEQ