//
// Created by vladl on 06/07/2020.
//
#pragma once

#ifndef ENG1_ARRAY_H
#define ENG1_ARRAY_H

#include <exception>
#include <bits/c++config.h>
#include <string>
#include <iostream>
#include "../defs/types.h"

namespace EngineUtility {
    class [[maybe_unused]] EngineArrayOutOfBounds : public std::exception{
        [[nodiscard]] const char* what() const noexcept override;
    };

    template <class T>
    class [[maybe_unused]] Array {
    private:
        T** _arrPtr {nullptr};
        std::size_t _arrLen {0};
        std::size_t _arrCap {0};

        constexpr static const std::size_t MAX_ARR_SIZE   = SIZE_MAX;
        constexpr static const std::size_t NO_INDEX_GIVEN = -SIZE_MAX;

        void _alloc(std::size_t) noexcept;
        void _relocateMemory(std::size_t) noexcept;
    public:
        [[maybe_unused]] Array()                        noexcept;
        [[maybe_unused]] Array(const Array&)            noexcept;
        [[maybe_unused]] Array(const T*, std::size_t)   noexcept(false);

        ~Array() noexcept;

        [[maybe_unused]] [[nodiscard]] std::size_t getLength()   const noexcept;
        [[maybe_unused]] [[nodiscard]] std::size_t getSize()     const noexcept;
        [[maybe_unused]] [[nodiscard]] std::size_t getByteSize() const noexcept;

        [[maybe_unused]] [[nodiscard]] T& operator[] (std::size_t)   noexcept(false);
        [[maybe_unused]] [[nodiscard]] T& get(std::size_t)           noexcept(false);

        [[maybe_unused]] void insert(const T&, std::size_t = NO_INDEX_GIVEN)                noexcept (false);
        [[maybe_unused]] void insert(const Array<T>&, std::size_t = NO_INDEX_GIVEN)         noexcept(false);
        [[maybe_unused]] void insert(const T*, std::size_t, std::size_t = NO_INDEX_GIVEN)   noexcept(false);

        [[maybe_unused]] [[nodiscard]] int64 find(const T&)                 noexcept;
        [[maybe_unused]] [[nodiscard]] int64 find(const Array<T>&)          noexcept;
        [[maybe_unused]] [[nodiscard]] int64 find(const T*, std::size_t)    noexcept;

        template <class U> friend Array<U> operator+ (const Array<U>&, const Array<U>&) noexcept(false);
        template <class U> friend Array<U> operator+ (const Array<U>&, const U&)        noexcept(false);

        Array<T>& operator= (const Array<T>&) noexcept;

        Array<T>& operator+= (const Array<T>&)  noexcept(false);
        Array<T>& operator+= (const T&)         noexcept(false);

        template <class U> friend bool operator == (const Array<U>&, const Array<U>&) noexcept;
        template <class U> friend bool operator != (const Array<U>&, const Array<U>&) noexcept;

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
        [[maybe_unused]] void shrink() noexcept;

        [[maybe_unused]] explicit operator std::string () const;

        template <class U> friend std::ostream& operator << (std::ostream& f, const EngineUtility::Array<U>& array) {
            f << "arr = [ ";
            for( std::size_t iterator = 0; iterator < array._arrLen - 1; iterator++ )
                f << * ( array._arrPtr[iterator] ) << ", ";

            if(array._arrLen > 0)
                f << * ( array._arrPtr[array._arrLen - 1] );

            f<< " ] ";

            return f;
        }
    };
}

template <class T>
void EngineUtility::Array<T>::_alloc(std::size_t requiredSize) noexcept {
    if(requiredSize + this->_arrLen <= this->_arrCap)
        return;

    std::size_t newSize = (this->_arrLen + requiredSize > 2 * this->_arrCap ) ? (this->_arrLen + requiredSize) : (2 * this->_arrCap);

    if( newSize > MAX_ARR_SIZE )
        newSize = MAX_ARR_SIZE;

    this->_relocateMemory(newSize);
}

template <class T>
void EngineUtility::Array<T>::_relocateMemory(std::size_t blockSize) noexcept {
    T** newMemLoc = new T * [blockSize];

    for( std::size_t iterator = 0; iterator < blockSize; iterator++ ) {
        if( iterator < this->_arrLen )
            newMemLoc[iterator] = this->_arrPtr[iterator];
        else
            newMemLoc[iterator] = new T;
    }

    for( std::size_t iterator = this->_arrLen; iterator < this->_arrCap; iterator++ ){
        delete newMemLoc[iterator];
    }

    delete[] this->_arrPtr;

    this->_arrPtr = newMemLoc;
    this->_arrCap = blockSize;
}

template <class T>
[[maybe_unused]] inline EngineUtility::Array<T>::Array() noexcept = default;

template <class T>
[[maybe_unused]] inline EngineUtility::Array<T>::Array(const EngineUtility::Array<T>& array) noexcept {
    this->_alloc(array._arrCap);

    for( ; this->_arrLen < array._arrLen; this->_arrLen++ ) {
        * ( this->_arrPtr[this->_arrLen] ) = * ( array._arrPtr[this->_arrLen] );
    }
}

template <class T>
[[maybe_unused]] inline EngineUtility::Array<T>::Array(const T * array, std::size_t length) noexcept(false) {
    if(length < 0 || length >= MAX_ARR_SIZE )
        throw EngineUtility::EngineArrayOutOfBounds();

    this->_alloc(length);

    for( ; this->_arrLen < length; this->_arrLen++ ) {
        * ( this->_arrPtr[this->_arrLen] ) = array[this->_arrLen];
    }
}

template <class T>
inline EngineUtility::Array<T>::~Array() noexcept {
    for( std::size_t iterator = 0; iterator < this->_arrCap; iterator++ ) {
        delete this->_arrPtr[iterator];
    }

    delete[] this->_arrPtr;
}

template <class T>
[[maybe_unused]] [[nodiscard]] inline std::size_t EngineUtility::Array<T>::getLength() const noexcept {
    return this->_arrLen;
}

template <class T>
[[maybe_unused]] [[nodiscard]] inline std::size_t EngineUtility::Array<T>::getSize() const noexcept {
    return this->_arrCap;
}

template <class T>
[[maybe_unused]] [[nodiscard]] inline std::size_t EngineUtility::Array<T>::getByteSize() const noexcept {
    return this->_arrCap * sizeof(T);
}

template <class T>
[[maybe_unused]] [[nodiscard]] T& EngineUtility::Array<T>::operator[] (std::size_t index) noexcept(false) {
    if( index < 0 || index >= MAX_ARR_SIZE )
        throw EngineUtility::EngineArrayOutOfBounds();

    if( index >= this->_arrCap )
        this->_alloc(index - this->_arrCap + 1);

    if( index >= this->_arrLen )
        this->_arrLen = index + 1;

    return * ( this->_arrPtr[index] );
}

template <class T>
[[maybe_unused]] [[nodiscard]] T& EngineUtility::Array<T>::get(std::size_t index) noexcept(false) {
    if( index < 0 || index >= this->_arrLen )
        throw EngineUtility::EngineArrayOutOfBounds();

    return * ( this->_arrPtr[index] );
}

template <class T>
[[maybe_unused]] void EngineUtility::Array<T>::insert(const T & obj, std::size_t index) noexcept(false) {
    (*this)[index] = obj;
}

template <class T>
[[maybe_unused]] void EngineUtility::Array<T>::insert(const EngineUtility::Array<T>& array, std::size_t index) noexcept (false){
    // TODO
}

template <class T>
[[maybe_unused]] void EngineUtility::Array<T>::insert(const T *, std::size_t, std::size_t) noexcept(false) {
    // TODO
}

template <class T>
[[maybe_unused]] [[nodiscard]] int64 EngineUtility::Array<T>::find(const T& obj) noexcept {
    for( std::size_t iterator = 0; iterator < this->_arrLen; iterator++ ) {
        if ( * ( this->_arrPtr[iterator] ) == obj )
            return iterator;
    }
    return -1;
}

template <class T>
[[maybe_unused]] [[nodiscard]] int64 EngineUtility::Array<T>::find(const EngineUtility::Array<T> & array) noexcept {
    std::size_t subsequenceIterator = 0;

    for( std::size_t iterator = 0; iterator < this->_arrLen; iterator++ ) {
        while ( * ( this->_arrPtr[iterator + subsequenceIterator] ) == * ( array._arrPtr[subsequenceIterator] ) && subsequenceIterator < this->_arrLen )
            subsequenceIterator++;

        if(subsequenceIterator == array._arrLen)
            return iterator - subsequenceIterator + 1;

        subsequenceIterator = 0;
    }

    return -1;
}

template <class T>
[[maybe_unused]] [[nodiscard]] int64 EngineUtility::Array<T>::find(const T * array, std::size_t length) noexcept {
    std::size_t subsequenceIterator = 0;

    for( std::size_t iterator = 0; iterator < this->_arrLen; iterator++ ) {
        while( * ( this->_arrPtr[iterator + subsequenceIterator] ) == array[subsequenceIterator] && subsequenceIterator < this->_arrLen )
            subsequenceIterator++;

        if(subsequenceIterator == length)
            return iterator - subsequenceIterator + 1;

        subsequenceIterator = 0;
    }

    return -1;
}

template <class U>
EngineUtility::Array<U> operator+ (const EngineUtility::Array<U>& a, const EngineUtility::Array<U>& b) noexcept (false) {
    if(a._arrLen + b._arrLen > SIZE_MAX)
        throw EngineUtility::EngineArrayOutOfBounds();

    EngineUtility::Array<U> result = a;

    a._alloc(b._arrLen);

    for( std::size_t iterator = 0; iterator < b._arrLen; iterator++ ) {
        * ( result._arrPtr[iterator + a._arrLen] ) = * ( b._arrPtr[iterator] );
    }

    return result;
}

template <class U>
EngineUtility::Array<U> operator+ (const EngineUtility::Array<U>& array, const U& obj) noexcept(false) {
    if(array._arrLen == SIZE_MAX)
        throw EngineUtility::EngineArrayOutOfBounds();

    EngineUtility::Array<U> result = array;
    result.alloc(1);

    * (result._arrPtr[result._arrLen++] ) = obj;

    return result;
}

template <class T>
EngineUtility::Array<T>& EngineUtility::Array<T>::operator= (const EngineUtility::Array<T>& array) noexcept {
    if( this == &array )
        return *this;

    if( this->_arrCap > 0 ) {
        for( std::size_t iterator = 0; iterator < this->_arrCap; iterator++ )
            delete this->_arrPtr[iterator];
        delete[] this->_arrPtr;
    }

    this->_arrLen = this->_arrCap = 0;
    this->_alloc(array._arrCap);

    for( ; this->_arrLen < array._arrLen; this->_arrLen++ )
        * ( this->_arrPtr[this->_arrLen] ) = * ( array._arrPtr[this->_arrLen] );

    return *this;
}

template <class T>
EngineUtility::Array<T>& EngineUtility::Array<T>::operator+= (const EngineUtility::Array<T>& array) noexcept(false) {
    if( this->_arrLen + array._arrLen > MAX_ARR_SIZE )
        throw EngineUtility::EngineArrayOutOfBounds();

    this->_alloc(array._arrLen);

    for( std::size_t iterator = 0; iterator < array._arrLen; iterator++ )
        * ( this->_arrPtr[ this->_arrLen + iterator ] ) = * ( array._arrPtr[iterator] );

    this->_arrLen += array._arrLen;

    return *this;
}

template <class T>
EngineUtility::Array<T>& EngineUtility::Array<T>::operator+= (const T& obj) noexcept(false) {
    if( this->_arrLen == MAX_ARR_SIZE )
        throw EngineUtility::EngineArrayOutOfBounds();

    this->_alloc(1);

    * ( this->_arrPtr[ this->_arrLen++ ] ) = obj;

    return *this;
}

template <class U>
bool operator == (const EngineUtility::Array<U>& a, const EngineUtility::Array<U>& b) noexcept {
    return ! ( a != b );
}

template <class U>
bool operator != (const EngineUtility::Array<U>& a, const EngineUtility::Array<U>& b) noexcept {
    if( a._arrLen != b._arrLen )
        return false;

    for( std::size_t iterator = 0; iterator < a._arrLen; iterator++ )
        if( * ( a._arrPtr[iterator] ) != * ( b._arrPtr[iterator] ) )
            return false;

    return true;
}

template <class T>
[[maybe_unused]] [[nodiscard]] std::string EngineUtility::Array<T>::toString() const noexcept {
    std::string result = "Array = [ ";

    for( std::size_t iterator = 0; iterator < this->_arrLen; iterator++ )
        result += (std::string) ( * ( this->_arrPtr[iterator] ) ) + ", ";

    result.replace(result.length() - 2, result.length(), "");

    return result + " ]";
}

template<class T>
EngineUtility::Array<T>::operator std::string() const {
    return this->toString();
}

template<class T>
[[maybe_unused]] void EngineUtility::Array<T>::shrink() noexcept {
    if( this->_arrLen == this->_arrCap )
        return;

    this->_relocateMemory(this->_arrLen);
}

#endif //ENG1_ARRAY_H
