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
Sequence<T>* ListSequence<T>::getSubSequence( const int startIndex, const int endIndex ) const {
    if (   startIndex < 0 || endIndex < 0 ||
    startIndex > endIndex || startIndex >= this->getSize() || endIndex >= this->getSize() ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    try {
        ListSequence<T>* res = new ListSequence<T>();
        for ( int index = startIndex; index < endIndex; index++ ) {
            res->append( (*this)[index] );
        }
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
Sequence<T>* ListSequence<T>::concat( const Sequence<T>& other ) {
    try {
        for ( int index = 0; index < other.getSize(); index++ ) {
            this->append( other[index] );
        }
        return this;
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
Sequence<T>* ListSequence<T>::appendImmutable( const T& value ) const {
    try {
        return new ListSequence<T>(*this->list.appendImmutable(value));
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
Sequence<T>* ListSequence<T>::prependImmutable( const T& value ) const {
    try {
        return new ListSequence<T>(*this->list.prependImmutable(value));
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
Sequence<T>* ListSequence<T>::insertAtImmutable( const T& value, const int pos ) const {
    try {
        return new ListSequence<T>(*this->list.insertAtImmutable(value, pos));
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
Sequence<T>* ListSequence<T>::removeAtImmutable( const int pos ) const {
    try {
        return new ListSequence<T>(*this->list.popImmutable(pos));
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
Sequence<T>* ListSequence<T>::setAtImmutable( const T& value, const int pos ) const {
    try {
        return new ListSequence<T>(*this->list.setAtImmutable(value, pos));
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
Sequence<T>* ListSequence<T>::swapImmutable(const int pos1, const int pos2) const {
    try {
        return new ListSequence<T>(*this->list.swapImmutable(pos1, pos2));
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
Sequence<T>* ListSequence<T>::concatImmutable( const Sequence<T>& other ) const {
    try {
        ListSequence<T>* res = new ListSequence<T>(*this);
        for ( int index = 0; index < other.getSize(); index++ ) {
            res->append( other[index] );
        }
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
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