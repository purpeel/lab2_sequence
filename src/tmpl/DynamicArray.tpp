#include <iostream>
#include <cstdlib>

template <typename T>
DynamicArray<T>::DynamicArray() {
    this->size = 0;
    this->capacity = 2;
    this->allocBegin = new T[this->capacity];
    this->data = this->allocBegin + 1;
    this->allocEnd = this->allocBegin + this->capacity;
}

template <typename T>
DynamicArray<T>::DynamicArray( int capacity ) {
    this->size = 0;
    this->capacity = capacity;
    this->allogBegin = new T[this->capacity];
    this->data = this->allocBegin + (this->capacity / 4 + 1);
    this->allocEnd = this->allocBegin + this->capacity;
}

template <typename T>
DynamicArray<T>::DynamicArray( const DynamicArray<T>& source ) {
    this->size = source.size;
    this->capacity = source.capacity;
    this->allocBegin = new T[this->capacity];
    this->data = this->allocBegin + (source.data - source.allocBegin);
    this->allocEnd = this->allocBegin + this->capacity;

    for ( int index = 0; index < this->size; index++ ) {
        this[index] = source[index];
    }
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=( const DynamicArray<T>& source ) {
    if ( this != &source ) {
        delete[] this->allocBegin;

        this->size = source.size;
        this->capacity = source.capacity;
        this->allocBegin = new T[this->capacity];
        this->data = this->allocBegin + (source.data - source.allocBegin);
        this->allocEnd = this->allocBegin + this->capacity;
        for ( int index = 0; index < this->size; index++ ) {
            this[index] = source[index];
        }
    }
    return *this;
}

template <typename T>
DynamicArray<T>::DynamicArray( DynamicArray<T>&& source ) {
    this->size = source.size;
    this->capacity = source.capacity;
    this->allocBegin = source.allocBegin;
    this->data = source.data;
    this->allocEnd = source.allocEnd;

    source.size = 0;
    source.capacity = 2;
    source.allocBegin = new T[source.capacity];
    source.data = source.allocBegin + 1;
    source.allocEnd = source.allocBegin + source.capacity;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=( DynamicArray<T>&& source ) {
    if ( this != &source ) {
        delete[] this->data;
        this->size = source.size;
        this->capacity = source.capacity;
        this->allocBegin = source.allocBegin;
        this->data = source.data;
        this->allocEnd = source.allocEnd;

        source.size = 0;
        source.capacity = 2;
        source.allocBegin = new T[source.capacity];
        source.data = source.allocBegin + 1;
        source.allocEnd = source.allocBegin + source.capacity;
    }
    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->allocBegin;
}

template <typename T>
void DynamicArray<T>::append( const T& value ) {
    int sizeDiff = 1;
    try {
        this->extend( sizeDiff );
        this[this->size - 1] = value;
    } catch( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void DynamicArray<T>::prepend( const T& value ) {
    int sizeDiff = 1;
    try {
        this->extend( sizeDiff );
        this->data--;
        this[0] = value;
    } catch( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void DynamicArray<T>::insertAt( const T& value, int pos ) {
    if ( pos < 0 || pos > this.size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    int sizeDiff = 1;
    try {
        this->extend( sizeDiff );
        for ( int index = pos; index < this->size; index++ ) {
            this[index + 1] = this[index];
        }
        this[pos] = value;
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void DynamicArray<T>::setAt( T& value, int pos ) {
    if ( pos < 0 || pos > this.size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    this->data[pos] = value;
}

template <typename T>
void DynamicArray<T>::removeAt( int pos ) {
    if ( pos < 0 || pos > this.size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    int sizeDiff = 1;
    try {
        T temp;
        for ( int index = pos; index < this->size - 1; index++ ) {
            temp = this[index];
            this[index] = this[index + 1];
            this[index + 1] = temp;
        }
        shrink( sizeDiff );
    } catch ( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void DynamicArray<T>::swap( int first, int second ) {
    if ( first < 0 || first > this->size || second < 0 || second > this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    T temp = this->data[first];
    this->data[first] = this->data[second];
    this->data[second] = temp;
}

template <typename T>
void DynamicArray<T>::extend( int sizeDiff ) {
    if ( sizeDiff < 0 ) {
        throw Exception( Exception::ErrorCode::NEGATIVE_SIZE_DIFFERENCE );
    }

    this->size += sizeDiff;
    int newCapacity = this->capacity;

    if ( newCapacity < 10000 ) {
        newCapacity = ( this->size > newCapacity * 0.75 ) 
            ? newCapacity * 2
            : newCapacity;
    } else {
        newCapacity = ( this->size > newCapacity * 0.25 )
            ? newCapacity + 1000
            : newCapacity;
    }
    try {
        if ( newCapacity != this->capacity ) {
            T* newAllocBegin = new T[newCapacity];
            T* newData = newAllocBegin + (newCapacity / 4 + 1);
            T* newAllocEnd = newAllocBegin + newCapacity;
            for ( int index = 0; index < this->size; index++ ) {
                newData[index] = this->data[index];
            }
            this->capacity = newCapacity;
            this->allocBegin = newAllocBegin;
            this->data = newData;
            this->allocEnd = newAllocEnd;    
        }
        delete[] this->allocBegin; 
    } catch( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
void DynamicArray<T>::shrink( int sizeDiff ) {
    if ( sizeDiff < 0 ) {
        throw Exception( Exception::ErrorCode::NEGATIVE_SIZE_DIFFERENCE );
    }

    this->size += sizeDiff;
    int newCapacity = this->capacity;

    if ( newCapacity < 10000 ) {
        newCapacity = ( this->size < newCapacity * 0.25 )
            ? newCapacity / 2
            : newCapacity;
    } else {
        newCapacity = ( this->size < newCapacity * 0.75 )
            ? newCapacity - 1000
            : newCapacity;
    }
    try {
        if ( newCapacity != this->capacity ) {
            T* newAllocBegin = new T[newCapacity];
            T* newData = newAllocBegin + (newCapacity / 4 + 1);
            T* newAllocEnd = newAllocBegin + newCapacity;
            for ( int index = 0; index < this->size; index++ ) {
                newData[index] = this->data[index];
            }
            this->capacity = newCapacity;
            this->allocBegin = newAllocBegin;
            this->data = newData;
            this->allocEnd = newAllocEnd;    
        }
        delete[] this->allocBegin; 
    } catch( std::bad_alloc &ex ) {
        throw Exception(ex);
    }
}

template <typename T>
T& DynamicArray<T>::operator[]( int index ) {
    if ( index < 0 || index >= this->size ) {
        throw Exception( Exception::ErrorCode::INDEX_OUT_OF_BOUNDS );
    }
    return this->data[index];
}

template <typename T>
void DynamicArray<T>::clear() {
    this->size = 0;
    this->capacity = 2;
    delete[] this->allocBegin;
    this->allocBegin = new T[this->capacity];
    this->data = this->allocBegin + (this->capacity / 4 + 1);
    this->allocEnd = this->allocBegin + this->capacity;
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return this->size;
}

template <typename T>
int DynamicArray<T>::getCapacity() const {
    return this->capacity;
}

template <typename T>
bool DynamicArray<T>::isEmpty() const {
    return this->size == 0;
}