#include <iostream>
#include <cstdlib>

template <typename T>
ListSequence<T>::ListSequence() : list() {}

template <typename T>
ListSequence<T>::ListSequence( const LinkedList<T>& src ) : list(src) {}

template <typename T>
ListSequence<T>::ListSequence( const ListSequence<T>& src ) : list(src.list) {}

template <typename T>
ListSequence<T>& ListSequence<T>::operator=( const LinkedList<T>& src ) {
    try {   
        this->list = src;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
ListSequence<T>& ListSequence<T>::operator=( const ListSequence<T>& src ) {
    try {
        this->list = src.list;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
ListSequence<T>::ListSequence(LinkedList<T>&& src) : list(std::move(src)) {}

template <typename T>
ListSequence<T>::ListSequence(ListSequence<T>&& src) : list(std::move(src.list)) {}


template <typename T>
ListSequence<T>& ListSequence<T>::operator=( LinkedList<T>&& src ) {
    try {
        this->list = src;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
ListSequence<T>& ListSequence<T>::operator=( ListSequence<T>&& src ) {
    try {
        this->list = src.list;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
    return *this;
}

template <typename T>
Sequence<T>* ListSequence<T>::clone() const {
    return new ListSequence<T>(*this);
}

template <typename T>
void ListSequence<T>::copy( const Sequence<T>& src ) {
    try {
        this->list = LinkedList<T>();
        for ( int index = 0; index < src.getSize(); index++ ) {
            this->list.append( src[index] );
        }
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
ListSequence<T>::~ListSequence() {
    this->list.~LinkedList();
}

template <typename T>
void ListSequence<T>::append( const T& value ) {
    this->list.append( value );
}

template <typename T>
void ListSequence<T>::prepend( const T& value ) {
    try {
        this->list.prepend( value );
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ListSequence<T>::insertAt( const T& value, const int pos ) {
    try {
        this->list.insertAt( value, pos );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ListSequence<T>::removeAt( const int pos ) {
    try {
        this->list.pop( pos );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ListSequence<T>::setAt( const T& value, const int pos ) {
    try {
        this->list.setAt( value, pos );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ListSequence<T>::swap( const int pos1, const int pos2 ) {
    try {
        this->list.swap( pos1, pos2 );
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
T& ListSequence<T>::operator[](const int pos) {
    try {
        return this->list[pos];
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
const T& ListSequence<T>::operator[](const int pos) const {
    try {
        return this->list[pos];
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
const bool ListSequence<T>::isEmpty() const {
    return this->list.isEmpty();
}

template <typename T>
const int ListSequence<T>::getSize() const {
    return this->list.getSize();
}

template <typename T>
const std::string ListSequence<T>::print() const {
    try {
        return this->list.print();
    } catch ( std::exception &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void ListSequence<T>::clear() {
    this->list.clear();
}