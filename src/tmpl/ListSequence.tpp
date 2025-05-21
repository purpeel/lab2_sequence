#include <iostream>
#include <cstdlib>

template <typename T>
ListSequence<T>::ListSequence() {
    this->list.LinkedList()
}

template <typename T>
ListSequence<T>::ListSequence( const int size ) {
    this->list.LinkedList( size );
}

template <typename T>
ListSequence<T>::ListSequence( const LinkedList<T>& src ) {
    this->list.LinkedList( src );
}

template <typename T>
ListSequence<T> ListSequence<T>::operator=( const LinkedList<T>& src ) {
    this->list = src;
    return *this;
}

template <typename T>
ListSequence<T>::ListSequence( LinkedList<T>&& src ) {
    this->list.LinkedList( src );
}  

template <typename T>
ListSequence<T> ListSequence<T>::operator=( LinkedList<T>&& src ) {
    this->list = src;
    return *this;
}

template <typename T>
ListSequence<T>::~ListSequence() {
    this->list.~LinkedList();
}

template <typename T>
void ListSequence<T>::append( const T& value ) override {
    this->list.append( value );
}

template <typename T>
void ListSequence<T>::prepend( const T& value ) override {
    this->list.prepend( value );
}

template <typename T>
void ListSequence<T>::insertAt( const T& value, const int pos ) override {
    try {
        this->list.insertAt( value, pos );
    } catch { std::exception& ex } {
        throw Exception::Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::removeAt( const int pos ) override {
    try {
        this->list.removeAt( pos );
    } catch { std::exception& ex } {
        throw Exception::Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::setAt( const T& value, const int pos ) override {
    try {
        this->list.setAt( value, pos );
    } catch { std::exception& ex } {
        throw Exception::Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::swap( const int pos1, const int pos2 ) override {
    try {
        this->array.swap( pos1, pos2 );
    } catch { std::exception& ex } {
        throw Exception::Exception(ex);
    }
}

template <typename T>
T& ListSequence<T>::operator[](const int pos) override {
    try {
        return this->list[pos];
    } catch { std::exception& ex } {
        throw Exception::Exception(ex);
    }
}

template <typename T>
const T& ListSequence<T>::operator[](const int pos) const override {
    try {
        return this->list[pos];
    } catch { std::exception& ex } {
        throw Exception::Exception(ex);
    }
}

template <typename T>
const bool ListSequence<T>::isEmpty() const override {
    return this->list.isEmpty();
}

template <typename T>
const int ListSequence<T>::getSize() const override {
    return this->list.getSize();
}