#ifndef LISTSEQ_H
#define LISTSEQ_H

#include "Sequence.hpp"
#include "LinkedList.hpp"

template <typename T>
class ListSequence : public Sequence<T>
{
public:
    ListSequence();

    ListSequence( const LinkedList<T>& src );
    ListSequence( const ListSequence<T>& src );
    ListSequence<T>& operator=( const LinkedList<T>& src );
    ListSequence<T>& operator=( const ListSequence<T>& src );

    ListSequence( LinkedList<T>&& src );
    ListSequence( ListSequence<T>&& src );
    ListSequence<T>& operator=( LinkedList<T>&& src );
    ListSequence<T>& operator=( ListSequence<T>&& src );

    Sequence<T>* clone() const override;

    void copy( const Sequence<T>& src ) override;
    void clear() override;
    virtual ~ListSequence();
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
public:
    const std::string print() const override;
private:
    LinkedList<T> list;
};

#include "../../src/tmpl/ListSequence.tpp"
#endif // LISTSEQ_H