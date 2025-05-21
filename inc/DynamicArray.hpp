#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "util.hpp"

template <typename T> 
class DynamicArray 
{
public:
    DynamicArray();
    DynamicArray( int capacity );

    DynamicArray( const DynamicArray<T>& src );
    DynamicArray<T>& operator=( const DynamicArray<T>& src );
    
    DynamicArray( DynamicArray<T>&& src);
    DynamicArray<T>& operator=( DynamicArray<T>&& src );
    
    virtual ~DynamicArray();
public:
    void append( const T& value );
    void prepend( const T& value );
    void setAt( T& value, int pos );
    void insertAt( const T& value, int pos );
    void removeAt( int pos );
    void swap( int pos1, int pos2 );
private:
    void extend( int sizeDiff );
    void shrink( int sizeDiff );
public:
    T& operator[]( int pos );
    const T& operator[]( int pos ) const;
public:
    int getSize() const;
    bool isEmpty() const;
private:
    int getCapacity() const;
    virtual void clear();
    T* allocBegin;
    T* data;
    T* allocEnd;
    int size;
    int capacity;
};


#include "../src/tmpl/DynamicArray.tpp"
#endif // DYNAMIC_ARRAY_H