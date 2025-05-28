#include <iostream>
#include <cstdlib>

template <typename T>
LinkedList<T>::LinkedList() {
    this->size = 0;
    this->head = this->tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList( const LinkedList<T>& source ) {
    this->size = 0;
    this->head = this->tail = nullptr;
    Node* current = source.head;
    while ( current ) {
        try {
            this->append( current->value );
            if ( !current->next ) { break; }
            current = current->next;
        } catch ( std::bad_alloc& ex ) {
            throw Exception(ex);
        }
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=( const LinkedList<T>& source ) {
    if ( this == &source ) { return *this; }

    this->clear();
    
    Node* current = source.head;
    while ( current != nullptr ) {
        this->append( current->value );
        current = current->next;
    }
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList( LinkedList<T>&& source ) {
    this->size = source.size;
    this->head = source.head;
    this->tail = source.tail;

    source.size = 0;
    source.head = source.tail = nullptr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=( LinkedList<T>&& source ){
    if ( this == &source ) { return *this; }
    this->clear();

    this->size = source.size;
    this->head = source.head;
    this->tail = source.tail;

    source.size = 0;
    source.head = source.tail = nullptr;
    
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    this->clear();
}

template <typename T>
void LinkedList<T>::clear() {
    if ( !this->isEmpty() ) {
        Node *current = this->head;
        while ( current->next ) {
            current = current->next;
            delete( current->prev );
        }
        delete( current );
        this->size = 0;
        this->head = this->tail = nullptr;
    }
}

template <typename T>
void LinkedList<T>::append( const T& value ) {
    try {
        Node* newElem = new Node;
        newElem->value = value;
        if ( this->isEmpty() ) {
            this->head = this->tail = newElem;
            this->size++;
            newElem->prev = newElem->next = nullptr;
        } else {
            newElem->prev = this->tail;
            newElem->next = nullptr;
            this->tail->next = newElem;
            this->tail = newElem;
            this->size++;
        }
    } catch ( std::bad_alloc& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void LinkedList<T>::prepend( const T& value ) {
    try { 
        Node* newElem = new Node;
        newElem->value = value;
        if ( this->isEmpty() ) {
            this->head = this->tail = newElem;
            this->size++;
            newElem->next = newElem->prev = nullptr;
        } else {
            newElem->next = this->head;
            newElem->prev = nullptr;
            this->head->prev = newElem;
            this->head = newElem;
            this->size++;
        }
    } catch ( std::bad_alloc& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void LinkedList<T>::setAt( const T& value, const int pos ) {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = this->head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }
    current->value = value;
} 

template <typename T>
void LinkedList<T>::insertAt( const T& value, const int pos ) {
    if ( pos < 0 || pos > this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    } else if ( pos == 0 ) {
        prepend( value );
    } else if ( pos == this->size ) {
        append( value );
    } else {
        Node* current = this->head;
        for ( int index = 0; index < pos; index++ ) {
            current = current->next;
        }
        Node* prev = current->prev;
        Node* next = current;
        Node* newElem = new Node;

        newElem->value = value;
        newElem->prev = prev;
        newElem->next = next;
        prev->next = next->prev = newElem;
        this->size++;
    }
} 

template <typename T>
void LinkedList<T>::pop( const int pos ) {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }

    if ( size == 1) {
        head = tail = nullptr;
    } else if ( current == head ) {
        head = head->next;
        head->prev = nullptr;
    } else if ( current == tail ) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    delete current;
    this->size--;
}

template <typename T>
void LinkedList<T>::swap( const int pos1, const int pos2 ) {
    if (pos1 < 0 || pos2 < 0 || pos1 >= this->size || pos2 >= this->size) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    } else if ( pos1 == pos2 ) {
        return;
    }

    T value1 = (*this)[pos1];
    T value2 = (*this)[pos2];

    this->pop(pos1);
    this->insertAt( value2, pos1 );
    this->pop(pos2);
    this->insertAt( value1, pos2 );
}

template <typename T>
LinkedList<T>* LinkedList<T>::subList( const int startIndex, const int endIndex ) const {
    if (   startIndex < 0 || endIndex < 0 ||
    startIndex > endIndex || startIndex >= this->getSize() || endIndex >= this->getSize() ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    try {
        LinkedList<T>* res = new LinkedList<T>();
        for ( int index = startIndex; index < endIndex; index++ ) {
            res->append( (*this)[index] );
        }
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::concat( const LinkedList<T>& other ) {
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
T& LinkedList<T>::operator[]( const int pos ) {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = this->head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }

    return current->value;
}

template <typename T>
const T& LinkedList<T>::operator[](const int pos ) const {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = this->head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }

    return current->value;
}

template <typename T>
const int LinkedList<T>::getSize() const {
    return this->size;
}

template <typename T>
const bool LinkedList<T>::isEmpty() const {
    return this->size == 0;
}

template <typename T>
LinkedList<T>* LinkedList<T>::appendImmutable( const T& value ) const {
    try {
        LinkedList<T>* res = new LinkedList<T>(*this);
        res->append( value );
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::prependImmutable( const T& value ) const {
    try {
        LinkedList<T>* res = new LinkedList<T>(*this);
        res->prepend( value );
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::insertAtImmutable( const T& value, const int pos ) const {
    try {
        LinkedList<T>* res = new LinkedList<T>(*this);
        res->insertAt( value, pos );
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::popImmutable( const int pos ) const {
    try {
        LinkedList<T>* res = new LinkedList<T>(*this);
        res->pop(pos);
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::setAtImmutable( const T& value, const int pos ) const {
    try {
        LinkedList<T>* res = new LinkedList<T>(*this);
        res->setAt( value, pos );
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::swapImmutable(const int pos1, const int pos2) const {
    try {
        LinkedList<T>* res = new LinkedList<T>(*this);
        res->swap(pos1, pos2);
        return res;
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::concatImmutable( const LinkedList<T>& other ) const {
    try {
        LinkedList<T>* res = new LinkedList<T>(*this);
        return res->concat(other);
    } catch ( Exception& ex ) {
        throw Exception(ex);
    }
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode( const int pos ) {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = this->head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }
    return current;
}

template <typename T>
const std::string LinkedList<T>::print() const {
    std::string result = "{";
    for ( int index = 0; index < this->size; index++ ) {
        result += std::to_string( this->operator[](index) ) + " ";
    }
    result += "}";
    return result;
}