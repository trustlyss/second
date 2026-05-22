#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <sstream>

template <typename T>
class SmartPointer {
public:
    explicit SmartPointer(T* ptr = nullptr);
    ~SmartPointer();

    SmartPointer(const SmartPointer&)            = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

    SmartPointer(SmartPointer&& other)            noexcept;
    SmartPointer& operator=(SmartPointer&& other) noexcept;

    T& operator*()  const;
    T* operator->() const;

    explicit operator bool() const;
    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;

    T*   get()            const;
    T*   release();
    void reset(T* ptr = nullptr);
    int  useCount()       const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const SmartPointer<U>& sp);

private:
    T*   ptr;
    int* refCount;

    void acquire(T* p, int* rc);
    void release_ref();
};

template <typename T>
SmartPointer<T>::SmartPointer(T* ptr)
    : ptr(ptr), refCount(ptr ? new int(1) : nullptr) {}

template <typename T>
SmartPointer<T>::~SmartPointer() {
    release_ref();
}

template <typename T>
SmartPointer<T>::SmartPointer(SmartPointer&& other) noexcept
    : ptr(other.ptr), refCount(other.refCount) {
    other.ptr      = nullptr;
    other.refCount = nullptr;
}

template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer&& other) noexcept {
    if (this != &other) {
        release_ref();
        ptr            = other.ptr;
        refCount       = other.refCount;
        other.ptr      = nullptr;
        other.refCount = nullptr;
    }
    return *this;
}

template <typename T>
T& SmartPointer<T>::operator*() const {
    if (!ptr) throw std::runtime_error("Dereferencing null SmartPointer");
    return *ptr;
}

template <typename T>
T* SmartPointer<T>::operator->() const {
    if (!ptr) throw std::runtime_error("Accessing member via null SmartPointer");
    return ptr;
}

template <typename T>
SmartPointer<T>::operator bool() const { return ptr != nullptr; }

template <typename T>
bool SmartPointer<T>::operator==(std::nullptr_t) const { return ptr == nullptr; }

template <typename T>
bool SmartPointer<T>::operator!=(std::nullptr_t) const { return ptr != nullptr; }

template <typename T>
T* SmartPointer<T>::get() const { return ptr; }

template <typename T>
T* SmartPointer<T>::release() {
    T* tmp   = ptr;
    ptr      = nullptr;
    refCount = nullptr;
    return tmp;
}

template <typename T>
void SmartPointer<T>::reset(T* p) {
    release_ref();
    ptr      = p;
    refCount = p ? new int(1) : nullptr;
}

template <typename T>
int SmartPointer<T>::useCount() const {
    return refCount ? *refCount : 0;
}

template <typename T>
void SmartPointer<T>::acquire(T* p, int* rc) {
    ptr      = p;
    refCount = rc;
    if (refCount) ++(*refCount);
}

template <typename T>
void SmartPointer<T>::release_ref() {
    if (refCount) {
        --(*refCount);
        if (*refCount == 0) {
            delete ptr;
            delete refCount;
        }
    }
    ptr      = nullptr;
    refCount = nullptr;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const SmartPointer<U>& sp) {
    if (sp.ptr)
        os << "SmartPointer -> " << *sp.ptr;
    else
        os << "SmartPointer -> null";
    return os;
}


struct Point {
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {}
    std::string toString() const {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << "Point(" << x << ", " << y << ")";
        return ss.str();
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << p.toString();
    }
};

struct Animal {
    std::string name;
    std::string species;
    int         age;
    Animal(const std::string& name, const std::string& species, int age)
        : name(name), species(species), age(age) {}
    void speak() const { std::cout << name << " says: ...\n"; }
    std::string toString() const {
        return "Animal{" + name + ", " + species + ", age=" + std::to_string(age) + "}";
    }
    friend std::ostream& operator<<(std::ostream& os, const Animal& a) {
        return os << a.toString();
    }
};