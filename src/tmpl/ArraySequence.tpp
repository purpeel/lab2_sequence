#include <iostream>
#include <cstdlib>

template <typename T>
ArraySequence<T>::ArraySequence() : array() {}

template <typename T>
ArraySequence<T>::ArraySequence( const int capacity ) : array(capacity) {}

template <typename T>
ArraySequence<T>::ArraySequence( const DynamicArray<T>& src ) : array(src) {}

template <typename T>
ArraySequence<T>::ArraySequence( const ArraySequence<T>& src ) : array(src.array) {}

template <typename T>
ArraySequence<T>& ArraySequence<T>::operator=( const DynamicArray<T>& src ) {
    try {
        this->array = src;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
ArraySequence<T>& ArraySequence<T>::operator=( const ArraySequence<T>& src ) {
    try {
        this->array = src.array;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
ArraySequence<T>::ArraySequence( DynamicArray<T>&& src ) : array(std::move(src)) {}

template <typename T>
ArraySequence<T>::ArraySequence( ArraySequence<T>&& src ) : array(std::move(src.array)) {}

template <typename T>
ArraySequence<T>& ArraySequence<T>::operator=( DynamicArray<T>&& src ) {
    try {
        this->array = src;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
ArraySequence<T>& ArraySequence<T>::operator=( ArraySequence<T>&& src ) {
    try {
        this->array = src.array;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
Sequence<T>* ArraySequence<T>::clone() const {
    try {
        return new ArraySequence<T>(*this);
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::copy( const Sequence<T>& src ) {
    if ( !this->isEmpty() ) {
        this->array.~DynamicArray();
    }
    try {
        this->array = DynamicArray<T>( 2 * src.getSize() );
        for ( int index = 0; index < src.getSize(); index++ ) {
            this->array.append( src[index] );
        }
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}   

template <typename T>
ArraySequence<T>::~ArraySequence() { }

template <typename T>
void ArraySequence<T>::append( const T& value ) {
    try {
        this->array.append( value );
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::prepend( const T& value ) {
    try {
        this->array.prepend( value );
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::insertAt( const T& value, const int pos ) {
    try {
        this->array.insertAt( value, pos );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::removeAt( const int pos ) {
    try {
        this->array.removeAt( pos );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::setAt( const T& value, const int pos ) {
    try {
        this->array.setAt( value, pos );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::swap( const int pos1, const int pos2 ) {
    try {
        this->array.swap( pos1, pos2 );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
T& ArraySequence<T>::operator[]( const int pos ) {
    try {
        return this->array[pos];
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
const T& ArraySequence<T>::operator[]( const int pos ) const {
    try {
        return this->array[pos];
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
const bool ArraySequence<T>::isEmpty() const {
    return this->array.isEmpty();
}

template <typename T>
const int ArraySequence<T>::getSize() const {
    return this->array.getSize();
}

template <typename T>
const std::string ArraySequence<T>::print() const {
    try {
        return this->array.print();
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ArraySequence<T>::clear() {
    this->array.clear();
}