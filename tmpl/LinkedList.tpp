#include <iostream>
#include <cstdlib>

template <typename T>
LinkedList<T>::LinkedList() {
    this->size = 0;
    this->head = this->tail = nullptr
}

template <typename T>
LinkedList<T>::LinkedList( const LinkedList<T>& source ) {
    Node* current = source.head;
    while ( current != nullptr ) {
        try {
            this->append( current->value )
            current = current->next;
        } catch ( std::bad_alloc& ex ) {
            throw Exception::Exception(ex);
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
LinkedList<T>::LinkedList( LinkedList<T>&& source ) noexcept {
    this->size = source.count;
    this->head = source.head;
    this->tail = source.tail;

    source.count = 0;
    source.head = source.tail = nullptr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=( LinkedList<T>&& source ) noexcept {
    if ( this == &source ) { return *this; }
    this->clear();

    this->size = source.count;
    this->head = source.head;
    this->tail = source.tail;

    source.count = 0;
    source.head = source.tail = nullptr;
    
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    this->clear();
}

template <typename T>
void LinkedList<T>::clear() override {
    if ( !this.isEmpty() ) {
        Node *current = this->head;
        while ( current->next != nullptr ) {
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
        throw Exception::Exception(ex);
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
            this->size++;
        }
    } catch ( std::bad_alloc& ex ) {
        throw Exception::Exception(ex);
    }
}

template <typename T>
void LinkedList<T>::setAt( T& value, const int pos ) {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception::Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
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
        throw Exception::Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    } else if ( pos == 0 ) {
        prepend( value );
    } else if ( pos == this->size ) {
        append( value );
    } else {
        Node* current = this->head;
        for ( int index = 1; index < pos; index++ ) {
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
        throw Exception::Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = this->head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    this->size--;
}

template <typename T>
void LinkedList<T>::swap( const int pos1, const int pos2 ) {
    Node* elem1 = this->getNode( pos1 );
    Node* elem2 = this->getNode( pos2 );
    Node temp = *elem1;

    elem1->next->prev = elem1->prev->next = elem2;
    elem2->next->prev = elem2->prev->next = elem1;

    elem1->next = elem2->next;
    elem1->prev = elem2->prev;
    elem2->next = temp.next;
    elem2->prev = temp.prev;
}

template <typename T>
T& LinkedList<T>::operator[]( const int pos ) {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception::Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
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
        throw Exception::Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = this->head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }

    return current->value;
}

template <typename T>
const int LinkedList<T>::getSize() {
    return this->size;
}

template <typename T>
const bool LinkedList<T>::isEmpty() {
    return this->size == 0;
}

template <typename T>
Node& LinkedList<T>::getNode( const int pos ) {
    if ( pos < 0 || pos >= this->size ) {
        throw Exception::Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    Node* current = this->head;
    for ( int index = 0; index < pos; index++ ) {
        current = current->next;
    }
    return *current;
}