#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <cstddef>

template <typename T, std::size_t N>
class StaticArray {
public:
    StaticArray();
    explicit StaticArray(const T& fill);

    T&       operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    T&       at(std::size_t index);
    const T& at(std::size_t index) const;

    T*       begin()        { return data; }
    T*       end()          { return data + N; }
    const T* begin()  const { return data; }
    const T* end()    const { return data + N; }

    constexpr std::size_t size() const { return N; }
    bool                  empty()const { return N == 0; }

    T    findMin() const;
    T    findMax() const;
    void fill(const T& value);
    void sort(bool ascending = true);

    void print(const std::string& label = "") const;

    template <typename U, std::size_t M>
    friend std::ostream& operator<<(std::ostream& os, const StaticArray<U, M>& a);

private:
    T data[N];
};

template <typename T>
class DynamicArray {
public:
    explicit DynamicArray(std::size_t capacity = 4);
    DynamicArray(std::size_t size, const T& fill);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    T&       operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    T&       at(std::size_t index);
    const T& at(std::size_t index) const;

    T*       begin()        { return data; }
    T*       end()          { return data + sz; }
    const T* begin()  const { return data; }
    const T* end()    const { return data + sz; }

    std::size_t size()     const { return sz; }
    std::size_t capacity() const { return cap; }
    bool        empty()    const { return sz == 0; }

    void pushBack(const T& value);
    void pushBack(T&& value);
    void popBack();
    void insert(std::size_t index, const T& value);
    void erase(std::size_t index);
    void clear();
    void reserve(std::size_t newCap);
    void resize(std::size_t newSize, const T& fill = T{});

    T    findMin() const;
    T    findMax() const;
    void sort(bool ascending = true);

    void print(const std::string& label = "") const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& a);

private:
    T*          data;
    std::size_t sz;
    std::size_t cap;

    void grow();
};


template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* ptr = nullptr);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    T& operator*()  const;
    T* operator->() const;

    explicit operator bool()      const { return ptr != nullptr; }
    bool     operator==(std::nullptr_t) const { return ptr == nullptr; }
    bool     operator!=(std::nullptr_t) const { return ptr != nullptr; }

    T*          get()      const { return ptr; }
    std::size_t useCount() const { return refCount ? *refCount : 0; }

    void reset(T* newPtr = nullptr);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const SharedPtr<U>& sp);

private:
    T*           ptr;
    std::size_t* refCount;

    void release();
};

template <typename T, std::size_t N>
StaticArray<T, N>::StaticArray() {
    static_assert(N > 0, "StaticArray size must be > 0");
    for (std::size_t i = 0; i < N; ++i) data[i] = T{};
}

template <typename T, std::size_t N>
StaticArray<T, N>::StaticArray(const T& fill) {
    static_assert(N > 0, "StaticArray size must be > 0");
    for (std::size_t i = 0; i < N; ++i) data[i] = fill;
}

template <typename T, std::size_t N>
T& StaticArray<T, N>::operator[](std::size_t i) { return data[i]; }

template <typename T, std::size_t N>
const T& StaticArray<T, N>::operator[](std::size_t i) const { return data[i]; }

template <typename T, std::size_t N>
T& StaticArray<T, N>::at(std::size_t i) {
    if (i >= N) throw std::out_of_range("StaticArray::at — index out of range");
    return data[i];
}

template <typename T, std::size_t N>
const T& StaticArray<T, N>::at(std::size_t i) const {
    if (i >= N) throw std::out_of_range("StaticArray::at — index out of range");
    return data[i];
}

template <typename T, std::size_t N>
T StaticArray<T, N>::findMin() const {
    T result = data[0];
    for (std::size_t i = 1; i < N; ++i) if (data[i] < result) result = data[i];
    return result;
}

template <typename T, std::size_t N>
T StaticArray<T, N>::findMax() const {
    T result = data[0];
    for (std::size_t i = 1; i < N; ++i) if (data[i] > result) result = data[i];
    return result;
}

template <typename T, std::size_t N>
void StaticArray<T, N>::fill(const T& value) {
    for (std::size_t i = 0; i < N; ++i) data[i] = value;
}

template <typename T, std::size_t N>
void StaticArray<T, N>::sort(bool ascending) {
    if (ascending) std::sort(begin(), end(), [](const T& a, const T& b){ return a < b; });
    else           std::sort(begin(), end(), [](const T& a, const T& b){ return a > b; });
}

template <typename T, std::size_t N>
void StaticArray<T, N>::print(const std::string& label) const {
    if (!label.empty()) std::cout << label << ": ";
    std::cout << "StaticArray<" << N << ">[ ";
    for (std::size_t i = 0; i < N; ++i)
        std::cout << data[i] << (i+1<N ? ", " : " ");
    std::cout << "]\n";
}

template <typename U, std::size_t M>
std::ostream& operator<<(std::ostream& os, const StaticArray<U, M>& a) {
    os << "[ ";
    for (std::size_t i = 0; i < M; ++i)
        os << a.data[i] << (i+1<M ? ", " : " ");
    os << "]";
    return os;
}

template <typename T>
DynamicArray<T>::DynamicArray(std::size_t capacity)
    : data(new T[capacity]), sz(0), cap(capacity) {}

template <typename T>
DynamicArray<T>::DynamicArray(std::size_t size, const T& fill)
    : data(new T[size]), sz(size), cap(size) {
    for (std::size_t i = 0; i < sz; ++i) data[i] = fill;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& o)
    : data(new T[o.cap]), sz(o.sz), cap(o.cap) {
    std::copy(o.data, o.data + o.sz, data);
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& o) noexcept
    : data(o.data), sz(o.sz), cap(o.cap) {
    o.data = nullptr; o.sz = 0; o.cap = 0;
}

template <typename T>
DynamicArray<T>::~DynamicArray() { delete[] data; }

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& o) {
    if (this != &o) {
        delete[] data;
        cap  = o.cap; sz = o.sz;
        data = new T[cap];
        std::copy(o.data, o.data + sz, data);
    }
    return *this;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& o) noexcept {
    if (this != &o) {
        delete[] data;
        data = o.data; sz = o.sz; cap = o.cap;
        o.data = nullptr; o.sz = 0; o.cap = 0;
    }
    return *this;
}

template <typename T>
T& DynamicArray<T>::operator[](std::size_t i) { return data[i]; }

template <typename T>
const T& DynamicArray<T>::operator[](std::size_t i) const { return data[i]; }

template <typename T>
T& DynamicArray<T>::at(std::size_t i) {
    if (i >= sz) throw std::out_of_range("DynamicArray::at — index out of range");
    return data[i];
}

template <typename T>
const T& DynamicArray<T>::at(std::size_t i) const {
    if (i >= sz) throw std::out_of_range("DynamicArray::at — index out of range");
    return data[i];
}

template <typename T>
void DynamicArray<T>::grow() {
    std::size_t newCap = cap == 0 ? 1 : cap * 2;
    T* newData = new T[newCap];
    std::copy(data, data + sz, newData);
    delete[] data;
    data = newData;
    cap  = newCap;
}

template <typename T>
void DynamicArray<T>::pushBack(const T& value) {
    if (sz == cap) grow();
    data[sz++] = value;
}

template <typename T>
void DynamicArray<T>::pushBack(T&& value) {
    if (sz == cap) grow();
    data[sz++] = std::move(value);
}

template <typename T>
void DynamicArray<T>::popBack() {
    if (sz == 0) throw std::underflow_error("DynamicArray::popBack — array is empty");
    --sz;
}

template <typename T>
void DynamicArray<T>::insert(std::size_t index, const T& value) {
    if (index > sz) throw std::out_of_range("DynamicArray::insert — index out of range");
    if (sz == cap) grow();
    for (std::size_t i = sz; i > index; --i) data[i] = data[i-1];
    data[index] = value;
    ++sz;
}

template <typename T>
void DynamicArray<T>::erase(std::size_t index) {
    if (index >= sz) throw std::out_of_range("DynamicArray::erase — index out of range");
    for (std::size_t i = index; i + 1 < sz; ++i) data[i] = data[i+1];
    --sz;
}

template <typename T>
void DynamicArray<T>::clear() { sz = 0; }

template <typename T>
void DynamicArray<T>::reserve(std::size_t newCap) {
    if (newCap <= cap) return;
    T* newData = new T[newCap];
    std::copy(data, data + sz, newData);
    delete[] data;
    data = newData;
    cap  = newCap;
}

template <typename T>
void DynamicArray<T>::resize(std::size_t newSize, const T& fill) {
    reserve(newSize);
    for (std::size_t i = sz; i < newSize; ++i) data[i] = fill;
    sz = newSize;
}

template <typename T>
T DynamicArray<T>::findMin() const {
    if (sz == 0) throw std::underflow_error("Array is empty");
    T result = data[0];
    for (std::size_t i = 1; i < sz; ++i) if (data[i] < result) result = data[i];
    return result;
}

template <typename T>
T DynamicArray<T>::findMax() const {
    if (sz == 0) throw std::underflow_error("Array is empty");
    T result = data[0];
    for (std::size_t i = 1; i < sz; ++i) if (data[i] > result) result = data[i];
    return result;
}

template <typename T>
void DynamicArray<T>::sort(bool ascending) {
    if (ascending) std::sort(begin(), end(), [](const T& a, const T& b){ return a < b; });
    else           std::sort(begin(), end(), [](const T& a, const T& b){ return a > b; });
}

template <typename T>
void DynamicArray<T>::print(const std::string& label) const {
    if (!label.empty()) std::cout << label << ": ";
    std::cout << "DynamicArray[sz=" << sz << ", cap=" << cap << "][ ";
    for (std::size_t i = 0; i < sz; ++i)
        std::cout << data[i] << (i+1<sz ? ", " : " ");
    std::cout << "]\n";
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& a) {
    os << "[ ";
    for (std::size_t i = 0; i < a.sz; ++i)
        os << a.data[i] << (i+1<a.sz ? ", " : " ");
    os << "]";
    return os;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr)
    : ptr(ptr), refCount(ptr ? new std::size_t(1) : nullptr) {}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& o)
    : ptr(o.ptr), refCount(o.refCount) {
    if (refCount) ++(*refCount);
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& o) noexcept
    : ptr(o.ptr), refCount(o.refCount) {
    o.ptr = nullptr; o.refCount = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr() { release(); }

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& o) {
    if (this != &o) {
        release();
        ptr      = o.ptr;
        refCount = o.refCount;
        if (refCount) ++(*refCount);
    }
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& o) noexcept {
    if (this != &o) {
        release();
        ptr = o.ptr; refCount = o.refCount;
        o.ptr = nullptr; o.refCount = nullptr;
    }
    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*() const {
    if (!ptr) throw std::runtime_error("SharedPtr: dereferencing null pointer");
    return *ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const {
    if (!ptr) throw std::runtime_error("SharedPtr: accessing member via null pointer");
    return ptr;
}

template <typename T>
void SharedPtr<T>::reset(T* newPtr) {
    release();
    ptr      = newPtr;
    refCount = newPtr ? new std::size_t(1) : nullptr;
}

template <typename T>
void SharedPtr<T>::release() {
    if (refCount) {
        --(*refCount);
        if (*refCount == 0) {
            delete ptr;
            delete refCount;
        }
    }
    ptr = nullptr; refCount = nullptr;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const SharedPtr<U>& sp) {
    if (sp.ptr) os << "SharedPtr[refs=" << *sp.refCount << "] -> " << *sp.ptr;
    else        os << "SharedPtr[null]";
    return os;
}