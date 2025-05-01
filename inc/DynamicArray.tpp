#include <iostream>
#include <cstdlib>

template <typename T>
DynamicArray<T>::DynamicArray() {
    this->size = 0;
    this->capacity = 2;
    this->allocBegin = new T[this->capacity];
    this->data = this->allocBegin + (this->capacity / 4 + 1);
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
        this->data[index] = source.data[index];
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
            this->data[index] = source.data[index];
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
    delete[] this->data;
}

template <typename T>
ResultInfo<void> DynamicArray<T>::append( const T& value ) {
    int sizeDiff = 1;
    ResultInfo<void> resizeStatus = ResultInfo<int>
        ::Value( sizeDiff )
        .Map( [this](int x) { return this->extend(x); });

    if ( resizeStatus.IsOk() ) {
        this->data[this->size - 1] = value;
        return ResultInfo<void>::Value();
    } else {
        return resizeStatus;
    }
}

template <typename T>
ResultInfo<void> DynamicArray<T>::prepend( const T& value ) {
    int sizeDiff = 1;
    ResultInfo<void> resizeStatus = ResultInfo<int>
        ::Value( sizeDiff )
        .Map( [this](int x) { return this->extend(x); });

    if ( resizeStatus.IsOk() ) {
        this->data--;
        *(this->data) = value;
        return ResultInfo<void>::Value();
    } else {
        return resizeStatus;
    }
}

template <typename T>
ResultInfo<void> DynamicArrat<T>::insertAt( const T& value, int pos ) {
    if ( index < 0 || index > this.size ) {
        return ResultInfo<void>::Error( Exception(ErrorCode::INDEX_OUT_OF_BOUNDS) );
    }
    int sizeDiff = 1;
    ResultInfo<void> resizeStatus = ResultInfo<int>
        ::Value( sizeDiff )
        .Map( [this](int x) { return this->extend(x); });

    if ( resizeStatus.IsOk() ) {
        for ( size_t index = this->size; index > pos; index--) {
            this->data[index] = this->data[index - 1];
        }
        this->data[pos] = value;
        return ResultInfo<void>::Value();
    } else {
        return resizeStatus;
    }
}

template <typename T>
ResultInfo<void> DynamicArray<T>::setAt( T& value, int index ) {
    if ( index < 0 || index > this.size ) {
        return ResultInfo<void>::Error( Exception(ErrorCode::INDEX_OUT_OF_BOUNDS) );
    }
    this->data[index] = value;
    return ResultInfo<void>::Value();
}

template <typename T>
void DynamicArray<T>::pop( int pos ) {
    if (index >= this->size) {
        return ResultInfo<void>::Error( Exception(ErrorCode::INDEX_OUT_OF_BOUNDS) );
    }
    if (this->size == 0) {
        return ResultInfo<void>::Error( Exception(ErrorCode::EMPTY_ARRAY) );
    }
    int sizeDiff = this->getSize();
    ResultInfo<void> resizeStatus = ResultInfo<int>
        ::Value( sizeDiff )
        .Map( [this](int x) { return this->shrink(x); });

    if resizeStatus.IsOk() {
        for (size_t index = pos; index < this->size - 1; index++) {
            this->data[index] = this->data[index + 1];
        }
        return ResultInfo<void>::Value();
    } else {
        return resizeStatus;
    }
}

template <typename T>
ResultInfo<void> DynamicArray<T>::swap( int first, int second ) {
    if ( first < 0 || first > this->size || second < 0 || second > this->size ) {
        return ResultInfo<void>::Error( Exception(ErrorCode::INDEX_OUT_OF_BOUNDS) );
    }
    T temp = this->data[first];
    this->data[first] = this->data[second];
    this->data[second] = temp;
    return ResultInfo<void>::Value();
}

template <typename T>
ResultInfo<void> DynamicArray<T>::extend( int sizeDiff ) {
    if ( sizeDiff < 0 ) {
        return ResultInfo<void>::Error( Exception(ErrorCode::NEGATIVE_SIZE_DIFFERENCE) );
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

    if ( newCapacity != this->capacity ) {
        T* newAllocBegin = new T[newCapacity];
        T* newData = newAllocBegin + (newCapacity / 4 + 1);
        T* newAllocEnd = newAllocBegin + newCapacity;
        for ( int index = 0; index < this->size; index++ ) {
            newData[index] = this->data[index];
        }
    }
    delete[] this->allocBegin;

    this->capacity = newCapacity;
    this->allocBegin = newAllocBegin;
    this->data = newData;
    this->allocEnd = newAllocEnd;    

    
    return ResultInfo<void>::Value();
}

template <typename T>
ResultInfo<void> DynamicArray<T>::shrink( int sizeDiff ) {
    if ( sizeDiff < 0 ) {
        return ResultInfo<void>::Error( Exception(ErrorCode::NEGATIVE_SIZE_DIFFERENCE) );
    }

    this->size -= sizeDiff;
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

    if ( newCapacity != this->capacity ) {
        T* newAllocBegin = new T[newCapacity];
        T* newData = newAllocBegin + (newCapacity / 4 + 1);
        T* newAllocEnd = newAllocBegin + newCapacity;
        for ( int index = 0; index < this->size; index++ ) {
            newData[index] = this->data[index];
        }
    }
    delete[] this->allocBegin;

    this->capacity = newCapacity;
    this->allocBegin = newAllocBegin;
    this->data = newData;
    this->allocEnd = newAllocEnd;

    return ResultInfo<void>::Value();
}

template <typename T>
T& DynamicArray<T>::operator[]( int index ) {
    if ( index < 0 || index >= this->size ) {
        throw Exception(ErrorCode::INDEX_OUT_OF_BOUNDS);
    }
    return this->data[index];
}

template <typename T>
int DynamicArray<T>::getSize() {
    return this->size;
}

template <typename T>
int DynamicArray<T>::getCapacity() {
    return this->capacity;
}
