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
    Sequence<T>* getSubSequence( const int startIndex, const int endIndex ) const override;
    Sequence<T>* concat( const Sequence<T>& other ) override;
public:
    T& operator[]( const int pos ) override;
    const T& operator[]( const int pos ) const override;
public:
    const bool isEmpty() const override;
    const int getSize() const override;
public:
    Sequence<T>* appendImmutable( const T& value ) const override;
    Sequence<T>* prependImmutable( const T& value ) const override;
    Sequence<T>* insertAtImmutable( const T& value, const int pos ) const override;
    Sequence<T>* removeAtImmutable( const int pos ) const override;
    Sequence<T>* setAtImmutable( const T& value, const int pos ) const override;
    Sequence<T>* swapImmutable( const int pos1, const int pos2 ) const override;
    Sequence<T>* concatImmutable( const Sequence<T>& other ) const override;
public:
    const std::string print() const override;
private:
    LinkedList<T> list;
};

#include "../../src/tmpl/ListSequence.tpp"
#endif // LISTSEQ_H