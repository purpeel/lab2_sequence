#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "util.hpp"

template <typename T> 
class DynamicArray 
{
public:
    DynamicArray();
    DynamicArray( int capacity );

    DynamicArray( const DynamicArray<T>& source );
    DynamicArray<T>& operator=( const DynamicArray<T>& source );
    
    DynamicArray( DynamicArray<T>&& source);
    DynamicArray<T>& operator=( DynamicArray<T>&& source );
    
    virtual ~DynamicArray();
public:
    void append( const T& value );
    void prepend( const T& value );
    void setAt( T& value, int index );
    void insertAt( const T& value, int index );
    void pop( int index );
    void swap( int index1, int index2 );

    void extend( int sizeDiff );
    void shrink( int sizeDiff );
public:
    T& operator[]( int index );
    const T& operator[]( int index ) const;
public:
    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;
private:
    T* allocBegin;
    T* data;
    T* allocEnd;
    int size;
    int capacity;
};


#include "DynamicArray.tpp"
#endif