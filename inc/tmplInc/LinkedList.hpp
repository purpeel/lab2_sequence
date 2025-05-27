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

    LinkedList( LinkedList<T>&& src );
    LinkedList<T>& operator=( LinkedList<T>&& src );

    virtual ~LinkedList();
    virtual void clear();
public:
    void append( const T& value );
    void prepend( const T& value );
    void setAt( const T& value, const int pos );
    void insertAt( const T& value, const int pos );
    void pop( const int pos );
    void swap( const int pos1, const int pos2 );
    LinkedList<T>* subList( const int startIndex, const int endIndex ) const;
    LinkedList<T>* concat( const LinkedList<T>& other );
public:
    T& operator[]( const int pos );
    const T& operator[]( const int pos ) const;
public:
    const int getSize() const;
    const bool isEmpty() const;
public:
    LinkedList<T>* appendImmutable( const T& value ) const;
    LinkedList<T>* prependImmutable( const T& value ) const;
    LinkedList<T>* insertAtImmutable( const T& value, const int pos ) const;
    LinkedList<T>* popImmutable( const int pos ) const;
    LinkedList<T>* setAtImmutable( const T& value, const int pos ) const;
    LinkedList<T>* swapImmutable( const int pos1, const int pos2 ) const;
    LinkedList<T>* concatImmutable( const LinkedList<T>& other ) const;
public:
    const std::string print() const;
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };
    Node* getNode( const int pos );
    Node* head;
    Node* tail;
    int size;
};

#include "../../src/tmpl/LinkedList.tpp"
#endif // LINKEDLIST_H