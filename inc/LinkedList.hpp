#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "util.hpp"

template <typename T>
class LinkedList
{
public:
    LinkedList();

    LinkedList( const LinkedList<T>& src );
    LinkedList<T>& operator=( const LinkedList<T>& src );

    LinkedList( LinkedList<T>&& src ) noexcept;
    LinkedList<T>& operator=( LinkedList<T>&& src ) noexcept;

    virtual ~LinkedList();
public:
    void append( const T& value );
    void prepend( const T& value );
    void setAt( const T& value, const int pos );
    void insertAt( const T& value, const int pos );
    void pop( const int pos );
    void swap( const int pos1, const int pos2 );
public:
    T& operator[]( const int pos );
    const T& operator[]( const int pos ) const;
public:
    const int getSize() const;
    const bool isEmpty() const;
private:
    virtual void clear();
    Node& getNode( const int pos );
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    int size;
}

#include "../src/tmpl/LinkedList.tpp"
#endif // LINKEDLIST_H