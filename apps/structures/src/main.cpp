#include <iostream>
#include <stdexcept>
#include "../include/structures.hpp"

static void separator(const char* title) {
    std::cout << "\n==================================\n"
              << "  " << title
              << "\n==================================\n";
}

int main() {
    separator("Vector2D");
    Vec2 v2a = {3.0, 4.0};
    Vec2 v2b = {1.0, -2.0};
    std::cout << "a = " << v2a << "\n";
    std::cout << "b = " << v2b << "\n";
    std::cout << "a + b   = " << (v2a + v2b) << "\n";
    std::cout << "a - b   = " << (v2a - v2b) << "\n";
    std::cout << "a * b   = " << (v2a * v2b) << "\n";
    std::cout << "a * 2.5 = " << (v2a * 2.5) << "\n";
    std::cout << "3 * b   = " << (3.0 * v2b) << "\n";
    std::cout << "\nEnter Vec2:\n";
    Vec2 v2c; std::cin >> v2c;
    std::cout << "You entered: " << v2c << "\n";

    separator("Vector3D");
    Vec3 v3a = {1.0, 2.0, 3.0};
    Vec3 v3b = {4.0, 5.0, 6.0};
    std::cout << "a = " << v3a << "\n";
    std::cout << "b = " << v3b << "\n";
    std::cout << "a + b = " << (v3a + v3b) << "\n";
    std::cout << "a - b = " << (v3a - v3b) << "\n";
    std::cout << "a * b = " << (v3a * v3b) << "\n";
    std::cout << "a * 3 = " << (v3a * 3.0) << "\n";
    std::cout << "\nEnter Vec3:\n";
    Vec3 v3c; std::cin >> v3c;
    std::cout << "You entered: " << v3c << "\n";

    separator("Speed");
    Spd s1 = {72.0, SpeedUnit::KMH};
    Spd s2 = {10.0, SpeedUnit::MS};
    std::cout << "s1 = " << s1 << "\n";
    std::cout << "s2 = " << s2 << "\n";
    std::cout << "s1 + s2 = " << (s1 + s2) << "\n";
    std::cout << "s1 - s2 = " << (s1 - s2) << "\n";
    s1 += 18.0; std::cout << "s1 after += 18: " << s1 << "\n";
    s1 -= 36.0; std::cout << "s1 after -= 36: " << s1 << "\n";
    std::cout << "\nEnter Speed:\n";
    Spd s3; std::cin >> s3;
    std::cout << "You entered: " << s3 << "\n";

    separator("Car");
    Auto car = {"Toyota_Camry", 2022, 2.5, 850000.0};
    std::cout << car << "\n";
    car += 50000.0; std::cout << "\nAfter += 50000:\n" << car << "\n";
    car -= 30000.0; std::cout << "\nAfter -= 30000:\n" << car << "\n";
    std::cout << "\nEnter Car:\n";
    Auto car2; std::cin >> car2;
    std::cout << "\nYou entered:\n" << car2 << "\n";

    separator("Money");
    Cash m1 = {1500.0, "UAH"};
    Cash m2 = {2300.0, "UAH"};
    std::cout << "m1 = " << m1 << "\n";
    std::cout << "m2 = " << m2 << "\n";
    std::cout << "m1 + m2 = " << (m1 + m2)  << "\n";
    std::cout << "m2 - m1 = " << (m2 - m1)  << "\n";
    std::cout << "m1 * 3  = " << (m1 * 3.0) << "\n";
    std::cout << "2 * m2  = " << (2.0 * m2) << "\n";
    std::cout << "m1 * m2 = " << (m1 * m2)  << "\n";
    try {
        Cash bad = {100.0, "USD"};
        [[maybe_unused]] auto r = m1 + bad;
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    std::cout << "\nEnter Money:\n";
    Cash m3; std::cin >> m3;
    std::cout << "You entered: " << m3 << "\n";

    separator("Student");
    Stud st = {"Ivan_Ivanenko", 2022, "122", 3, 4.75};
    std::cout << st << "\n";
    std::cout << "\nEnter Student:\n";
    Stud st2; std::cin >> st2;
    std::cout << "\nYou entered:\n" << st2 << "\n";

    separator("Done");
    return 0;
}