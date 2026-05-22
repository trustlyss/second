#include "pointer.hpp"

#include <iostream>
#include <iomanip>

int main() {
    std::cout << "=== SmartPointer<int> ===\n";
    SmartPointer<int> sp1(new int(42));
    std::cout << "sp1 = " << sp1 << "\n";
    std::cout << "*sp1 = " << *sp1 << "\n";
    std::cout << "sp1.useCount() = " << sp1.useCount() << "\n";
    std::cout << "bool(sp1) = " << std::boolalpha << bool(sp1) << "\n";

    std::cout << "\n--- reset ---\n";
    sp1.reset(new int(100));
    std::cout << "After reset(100): *sp1 = " << *sp1 << "\n";

    std::cout << "\n--- release ---\n";
    int* raw = sp1.release();
    std::cout << "After release: bool(sp1) = " << bool(sp1) << "\n";
    std::cout << "Raw pointer value = " << *raw << "\n";
    delete raw;

    std::cout << "\n--- null pointer ---\n";
    SmartPointer<int> spNull;
    std::cout << "spNull == nullptr: " << (spNull == nullptr) << "\n";
    std::cout << "spNull != nullptr: " << (spNull != nullptr) << "\n";
    std::cout << spNull << "\n";

    std::cout << "\n=== SmartPointer<Point> ===\n";
    SmartPointer<Point> sp2(new Point(3.0, 4.0));
    std::cout << "sp2 = " << sp2 << "\n";
    std::cout << "*sp2 = " << *sp2 << "\n";
    std::cout << "sp2->x = " << sp2->x << "\n";
    std::cout << "sp2->y = " << sp2->y << "\n";
    std::cout << "sp2->toString() = " << sp2->toString() << "\n";

    std::cout << "\n--- modify via -> ---\n";
    sp2->x = 10.0;
    sp2->y = 20.0;
    std::cout << "After sp2->x=10, sp2->y=20: " << sp2 << "\n";

    std::cout << "\n=== SmartPointer<Animal> ===\n";
    SmartPointer<Animal> sp3(new Animal("Rex", "Dog", 3));
    std::cout << "sp3 = " << sp3 << "\n";
    std::cout << "sp3->name    = " << sp3->name    << "\n";
    std::cout << "sp3->species = " << sp3->species << "\n";
    std::cout << "sp3->age     = " << sp3->age     << "\n";
    sp3->speak();

    std::cout << "\n--- move semantics ---\n";
    SmartPointer<Animal> sp4 = std::move(sp3);
    std::cout << "After move:\n";
    std::cout << "  sp3 is null: " << (sp3 == nullptr) << "\n";
    std::cout << "  sp4 = " << sp4 << "\n";

    std::cout << "\n--- move assignment ---\n";
    SmartPointer<Animal> sp5(new Animal("Whiskers", "Cat", 2));
    std::cout << "sp5 before = " << sp5 << "\n";
    sp5 = std::move(sp4);
    std::cout << "sp5 after move from sp4 = " << sp5 << "\n";
    std::cout << "sp4 is null: " << (sp4 == nullptr) << "\n";

    std::cout << "\n--- destructor called automatically at end of scope ---\n";
    {
        SmartPointer<int> scoped(new int(999));
        std::cout << "Inside scope: *scoped = " << *scoped << "\n";
    }
    std::cout << "Outside scope: scoped destroyed, memory freed\n";

    return 0;
}