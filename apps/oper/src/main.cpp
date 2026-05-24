#include "oper.hpp"

static void section(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {

    section("StaticArray<int, 6>");
    StaticArray<int, 6> sa;
    int vals[] = {5, 3, 8, 1, 9, 2};
    for (int i = 0; i < 6; ++i) sa[i] = vals[i];
    sa.print("Initial");
    std::cout << "Min = " << sa.findMin() << ", Max = " << sa.findMax() << "\n";
    sa.sort();
    sa.print("Sorted asc ");
    sa.sort(false);
    sa.print("Sorted desc");
    std::cout << "sa[2] = " << sa[2] << "\n";
    std::cout << "operator<< : " << sa << "\n";

    section("StaticArray<double, 4>");
    StaticArray<double, 4> sd(3.14);
    sd[1] = 2.71; sd[3] = 1.41;
    sd.print("Initial");

    section("StaticArray bounds check");
    try { sa.at(99); }
    catch (const std::out_of_range& e) { std::cout << "Error: " << e.what() << "\n"; }

    section("DynamicArray<int>");
    DynamicArray<int> da;
    for (int v : {7, 2, 5, 1, 8, 3}) da.pushBack(v);
    da.print("After pushBack");
    std::cout << "size=" << da.size() << " cap=" << da.capacity() << "\n";
    std::cout << "Min = " << da.findMin() << ", Max = " << da.findMax() << "\n";

    da.insert(2, 99);
    da.print("After insert(2, 99)");
    da.erase(2);
    da.print("After erase(2)");
    da.popBack();
    da.print("After popBack");

    da.sort();
    da.print("Sorted asc ");
    da.sort(false);
    da.print("Sorted desc");

    section("DynamicArray copy & move");
    DynamicArray<int> copy = da;
    copy.print("Copy");
    DynamicArray<int> moved = std::move(copy);
    moved.print("Moved");
    std::cout << "copy.size() after move = " << copy.size() << "\n";

    section("DynamicArray<std::string>");
    DynamicArray<std::string> ds;
    ds.pushBack("banana");
    ds.pushBack("apple");
    ds.pushBack("cherry");
    ds.pushBack("date");
    ds.print("Before sort");
    ds.sort();
    ds.print("After sort ");

    section("DynamicArray resize & reserve");
    DynamicArray<int> dr;
    dr.reserve(10);
    std::cout << "After reserve(10): cap=" << dr.capacity() << "\n";
    dr.resize(5, 42);
    dr.print("After resize(5, 42)");

    section("SharedPtr<int> — shared ownership");
    SharedPtr<int> sp1(new int(100));
    std::cout << sp1 << "\n";
    {
        SharedPtr<int> sp2 = sp1;
        std::cout << "sp1: " << sp1 << "\n";
        std::cout << "sp2: " << sp2 << "\n";
        SharedPtr<int> sp3 = sp2;
        std::cout << "sp3: " << sp3 << "\n";
        *sp3 = 999;
        std::cout << "After *sp3=999, sp1: " << sp1 << "\n";
    }
    std::cout << "After sp2,sp3 out of scope, sp1: " << sp1 << "\n";

    section("SharedPtr — copy assignment");
    SharedPtr<int> spA(new int(1));
    SharedPtr<int> spB(new int(2));
    std::cout << "spA: " << spA << "\n";
    std::cout << "spB: " << spB << "\n";
    spA = spB;
    std::cout << "After spA=spB:\n";
    std::cout << "spA: " << spA << "\n";
    std::cout << "spB: " << spB << "\n";

    section("SharedPtr — move");
    SharedPtr<int> spC(new int(77));
    SharedPtr<int> spD = std::move(spC);
    std::cout << "spC after move: " << spC << "\n";
    std::cout << "spD after move: " << spD << "\n";

    section("SharedPtr — reset");
    spD.reset(new int(55));
    std::cout << "spD after reset(55): " << spD << "\n";
    spD.reset();
    std::cout << "spD after reset(): " << spD << "\n";

    section("SharedPtr<std::string>");
    SharedPtr<std::string> ss1(new std::string("hello"));
    SharedPtr<std::string> ss2 = ss1;
    std::cout << "ss1: " << ss1 << "\n";
    std::cout << "ss2->size() = " << ss2->size() << "\n";
    *ss1 = "world";
    std::cout << "After *ss1=\"world\", ss2: " << ss2 << "\n";

    return 0;
}