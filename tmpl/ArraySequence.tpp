#include <iostream>
#include <cstdlib>

template <typename T>
ArraySequence<T>::ArraySequence() {
    this->array.DynamicArray();
}

template <typename T>
ArraySequence<T>::ArraySequence( const int capacity ) {
    this->array.DynamicArray( capacity );
}

template <typename T>
ArraySequence<T>::ArraySequence( const DynamicArray<T>& src ) {
    this->array.DynamicArray( src );
}

template <typename T>
ArraySequence<T>& ArraySequence<T>::operator=( const DynamicArray<T>& src ) {
    this->array = src;
    return *this;
}

template <typename T>
ArraySequence<T>::ArraySequence( DynamicArray<T>&& src ) {
    this->array.DynamicArray( src );
}

template <typename T>
ArraySequence<T>& ArraySequence<T>::operator=( DynamicArray<T>&& src ) {
    this->array = src;
    return *this;
}

template <typename T>
ArraySequence<T>::~ArraySequence() {
    this->array.~DynamicArray();
}

template <typename T>
void ArraySequence<T>::append( const T& value ) override {
    this->array.append( value );
}

template <typaname T>
void ArraySequence<T>::prepend( const T& value ) override {
    this->array.prepend( value );
}

template <typename T>
void ArraySequence<T>::insertAt( const T& value, const int pos ) override {
    try {
        this->array.insertAt( value, pos );
    } catch ( std::exception &ex ) {
        throw Exception::Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::removeAt( const int pos ) override {
    try {
        this->array.removeAt( pos );
    } catch ( std::exception &ex ) {
        throw Exception::Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::setAt( const T& value, const int pos ) override {
    try {
        this->array.setAt( value, pos );
    } catch ( std::exception &ex ) {
        throw Exception::Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::swap( const int pos1, const int pos2 ) override {
    try {
        this->array.swap( pos1, pos2 );
    } catch ( std::exception &ex ) {
        throw Exception::Exception(ex);
    }
}

template <typename T>
T& ArraySequence<T>::operator[]( const int pos ) override {
    try {
        return this->array[pos];
    } catch ( std::exception &ex ) {
        throw Exception::Exception(ex);
    }
}

template <typename T>
const T& ArraySequence<T>::operator[]( const int pos ) const override {
    try {
        return this->array[pos];
    } catch ( std::exception &ex ) {
        throw Exception::Exception(ex);
    }
}

template <typename T>
const bool ArraySequence<T>::isEmpty() const override {
    return this->array.isEmpty();
}

template <typename T>
const int ArraySequence<T>::getSize() const override {
    return this->array.getSize();
}