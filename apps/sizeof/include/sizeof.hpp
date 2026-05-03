#pragma once
#include <iostream>

void printPrimitiveSizes() {
    std::cout << "=== Primitive type sizes ===" << std::endl;
    std::cout << "bool:               " << sizeof(bool)               << " byte(s)" << std::endl;
    std::cout << "char:               " << sizeof(char)               << " byte(s)" << std::endl;
    std::cout << "unsigned char:      " << sizeof(unsigned char)      << " byte(s)" << std::endl;
    std::cout << "short:              " << sizeof(short)              << " byte(s)" << std::endl;
    std::cout << "unsigned short:     " << sizeof(unsigned short)     << " byte(s)" << std::endl;
    std::cout << "int:                " << sizeof(int)                << " byte(s)" << std::endl;
    std::cout << "unsigned int:       " << sizeof(unsigned int)       << " byte(s)" << std::endl;
    std::cout << "long:               " << sizeof(long)               << " byte(s)" << std::endl;
    std::cout << "unsigned long:      " << sizeof(unsigned long)      << " byte(s)" << std::endl;
    std::cout << "long long:          " << sizeof(long long)          << " byte(s)" << std::endl;
    std::cout << "unsigned long long: " << sizeof(unsigned long long) << " byte(s)" << std::endl;
    std::cout << "float:              " << sizeof(float)              << " byte(s)" << std::endl;
    std::cout << "double:             " << sizeof(double)             << " byte(s)" << std::endl;
    std::cout << "long double:        " << sizeof(long double)        << " byte(s)" << std::endl;
    std::cout << "wchar_t:            " << sizeof(wchar_t)            << " byte(s)" << std::endl;
    std::cout << std::endl;
}

struct EmptyStruct {};

struct SmallStruct {
    int    age;
    double salary;
};

struct LargeStruct {
    int    age;
    double salary;
    char   grade;
    bool   active;
    long   id;
};

struct PointerStruct {
    int*    pAge;
    double* pSalary;
    char*   pName;
};

void printStructSizes() {
    std::cout << "=== Struct sizes ===" << std::endl;
    std::cout << "EmptyStruct:                     " << sizeof(EmptyStruct) << " byte(s)" << std::endl;
    std::cout << "SmallStruct (int + double):      " << sizeof(SmallStruct) << " byte(s)" << std::endl;
    std::cout << "LargeStruct (+char+bool+long):   " << sizeof(LargeStruct) << " byte(s)" << std::endl;
    std::cout << std::endl;

    SmallStruct  obj;
    SmallStruct* pObj = &obj;

    std::cout << "=== Pointer to struct ===" << std::endl;
    std::cout << "SmallStruct*:  " << sizeof(pObj)         << " byte(s)" << std::endl;
    std::cout << "LargeStruct*:  " << sizeof(LargeStruct*) << " byte(s)" << std::endl;
    std::cout << std::endl;

    std::cout << "=== Struct with pointer fields ===" << std::endl;
    std::cout << "PointerStruct (3 pointers):      " << sizeof(PointerStruct) << " byte(s)" << std::endl;
    std::cout << "  int*:    " << sizeof(int*)    << " byte(s)" << std::endl;
    std::cout << "  double*: " << sizeof(double*) << " byte(s)" << std::endl;
    std::cout << "  char*:   " << sizeof(char*)   << " byte(s)" << std::endl;
}