#ifndef ARRAYSEQ_H
#define ARRAYSEQ_H

#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <typename T>
class ArraySequence : public Sequence<T>
{
public:
    ArraySequence();
    ArraySequence( const int capacity );

    ArraySequence( const DynamicArray<T>& src );
    ArraySequence<T>& operator=( const DynamicArray<T>& src );

    ArraySequence( DynamicArray<T>&& src );
    ArraySequence<T>& operator=( DynamicArray<T>&& src );

    ~ArraySequence();
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
    DynamicArray<T> array;
};

#include "../src/tmpl/ArraySequence.tpp"
#endif // ARRAYSEQ_H