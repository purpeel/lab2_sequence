#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "util.hpp"

template <typename T>
class Sequence 
{
public:
    virtual Sequence() = 0;
    
    virtual Sequence( const Sequence<T>& src ) = 0;
    virtual Sequence<T> operator=( const Sequence<T>& src ) = 0;

    virtual Sequence( const Sequence<T>&& src ) = 0;
    virtual Sequence<T> operator=( const Sequence<T>&& src ) = 0;

    virtual ~Sequence() = 0;
public:
    virtual void append( const T& value );
    virtual void prepend( const T& value );
    virtual void insertAt( const T& value, const int pos );
    virtual void removeAt( const T& value, const int pos );
    virtual void setAt( const T& value, const int pos );
    virtual void swap( const int pos1, const int pos2 );
public:
    virtual T& operator[]( const int pos );
    virtual const T& operator[]( const int pos ) const;
public:
    virtual const bool isEmpty() const;
    virtual const int getSize() const;
};

#include "../tmpl/Sequence.tpp"

#endif