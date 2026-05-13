#include "tasks.hpp"

#include <iostream>
#include <iomanip>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

std::vector<double> randomDoubleVec(int size, double minVal, double maxVal) {
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    std::vector<double> v(size);
    std::generate(v.begin(), v.end(), [&]{ return dist(rng()); });
    return v;
}

std::vector<Car> randomCars(int count) {
    const std::vector<std::string> brands = {
        "Toyota", "BMW", "Ford", "Honda", "Tesla",
        "Audi",   "Kia", "Mazda","Volvo", "Nissan"
    };
    std::uniform_int_distribution<int>     yearDist (2015, 2024);
    std::uniform_real_distribution<double> speedDist(120.0, 320.0);
    std::uniform_real_distribution<double> priceDist(8000.0, 80000.0);
    std::uniform_int_distribution<int>     brandDist(0, (int)brands.size()-1);

    std::vector<Car> cars(count);
    for (auto& c : cars) {
        c.brand    = brands[brandDist(rng())];
        c.year     = yearDist(rng());
        c.maxSpeed = std::round(speedDist(rng()) * 10) / 10;
        c.price    = std::round(priceDist(rng()) * 100) / 100;
    }
    return cars;
}

std::vector<Student> randomStudents(int count) {
    const std::vector<std::string> names = {
        "Alice", "Bob", "Charlie", "Diana", "Edward",
        "Fiona", "George", "Hannah", "Ivan", "Julia"
    };
    std::uniform_int_distribution<int>     ageDist(17, 25);
    std::uniform_real_distribution<double> gpaDist(1.0, 5.0);
    std::uniform_int_distribution<int>     nameDist(0, (int)names.size()-1);

    std::vector<Student> students(count);
    for (auto& s : students) {
        s.name = names[nameDist(rng())];
        s.age  = ageDist(rng());
        s.gpa  = std::round(gpaDist(rng()) * 100) / 100;
    }
    return students;
}

Car fastestCar(const std::vector<Car>& cars) {
    return *std::max_element(cars.begin(), cars.end(),
        [](const Car& a, const Car& b) { return a.maxSpeed < b.maxSpeed; });
}

Car mostExpensiveCar(const std::vector<Car>& cars) {
    return *std::max_element(cars.begin(), cars.end(),
        [](const Car& a, const Car& b) { return a.price < b.price; });
}

Student topStudent(const std::vector<Student>& students) {
    return *std::max_element(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.gpa < b.gpa; });
}

static void printVec(const std::vector<double>& v) {
    std::cout << std::fixed << std::setprecision(4) << "[ ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << (i + 1 < v.size() ? ", " : " ");
    std::cout << "]\n";
}

static void printCars(const std::vector<Car>& cars) {
    std::cout << std::left
              << std::setw(10) << "Brand"
              << std::setw(6)  << "Year"
              << std::setw(12) << "Max Speed"
              << std::setw(12) << "Price"
              << "\n" << std::string(40, '-') << "\n";
    for (const auto& c : cars) {
        std::cout << std::left
                  << std::setw(10) << c.brand
                  << std::setw(6)  << c.year
                  << std::setw(12) << (std::to_string((int)c.maxSpeed) + " km/h")
                  << std::fixed << std::setprecision(2)
                  << "$" << c.price << "\n";
    }
}

static void printStudents(const std::vector<Student>& students) {
    std::cout << std::left
              << std::setw(10) << "Name"
              << std::setw(6)  << "Age"
              << std::setw(6)  << "GPA"
              << "\n" << std::string(22, '-') << "\n";
    for (const auto& s : students) {
        std::cout << std::left
                  << std::setw(10) << s.name
                  << std::setw(6)  << s.age
                  << std::fixed << std::setprecision(2) << s.gpa << "\n";
    }
}

int main() {
    std::vector<double> arr = randomDoubleVec(8, 1.0, 10.0);

    std::cout << "=== Task 1: Euclidean norm ===\n";
    std::cout << "Array:  "; printVec(arr);
    std::cout << "Result: " << std::fixed << std::setprecision(4)
              << euclideanNorm(arr) << "\n";

    std::cout << "\n=== Task 2: Divide each element by max ===\n";
    std::cout << "Original: "; printVec(arr);
    auto divided = divideByMax(arr);
    std::cout << "Result:   "; printVec(divided);

    std::cout << "\n=== Task 3: Multiply each element by min ===\n";
    std::cout << "Original: "; printVec(arr);
    auto multiplied = multiplyByMin(arr);
    std::cout << "Result:   "; printVec(multiplied);

    std::vector<Car> cars = randomCars(6);
    std::cout << "\n=== Task 4: Cars ===\n";
    printCars(cars);
    Car fastest = fastestCar(cars);
    Car priciest = mostExpensiveCar(cars);
    std::cout << "\nFastest car:       " << fastest.brand
              << " — " << fastest.maxSpeed << " km/h\n";
    std::cout << "Most expensive car: " << priciest.brand
              << " — $" << std::fixed << std::setprecision(2) << priciest.price << "\n";

    std::vector<Student> students = randomStudents(6);
    std::cout << "\n=== Task 5: Students ===\n";
    printStudents(students);
    Student top = topStudent(students);
    std::cout << "\nTop student: " << top.name
              << " — GPA: " << std::fixed << std::setprecision(2) << top.gpa << "\n";

    return 0;
}