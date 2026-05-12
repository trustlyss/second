#include "generator.hpp"

#include <iostream>
#include <iomanip>
#include <random>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

void fillIntArray(int* arr, int size, int minVal, int maxVal) {
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng());
}

void fillDoubleArray(double* arr, int size, double minVal, double maxVal) {
    std::uniform_real_distribution<double> dist(minVal, maxVal);
    for (int i = 0; i < size; ++i)
        arr[i] = dist(rng());
}

void printIntArray(const int* arr, int size) {
    std::cout << "[ ";
    for (int i = 0; i < size; ++i)
        std::cout << std::setw(4) << arr[i] << (i + 1 < size ? "," : " ");
    std::cout << " ]\n";
}

void printDoubleArray(const double* arr, int size) {
    std::cout << std::fixed << std::setprecision(2) << "[ ";
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << (i + 1 < size ? ", " : " ");
    std::cout << "]\n";
}

void fillStudents(Student* students, int count) {
    std::uniform_int_distribution<int>     ageDist  (17, 25);
    std::uniform_real_distribution<double> gpaDist  (1.0, 5.0);
    std::uniform_int_distribution<int>     scoreDist(0, 100);

    for (int i = 0; i < count; ++i) {
        students[i].id    = i + 1;
        students[i].age   = ageDist(rng());
        students[i].gpa   = gpaDist(rng());
        students[i].score = scoreDist(rng());
    }
}

void fillPoints(Point3D* points, int count) {
    std::uniform_real_distribution<double> dist(-100.0, 100.0);
    for (int i = 0; i < count; ++i) {
        points[i].x = dist(rng());
        points[i].y = dist(rng());
        points[i].z = dist(rng());
    }
}

void printStudent(const Student& s) {
    std::cout << std::fixed << std::setprecision(2)
              << "  Student #" << std::setw(2) << s.id
              << " | age: "    << std::setw(2) << s.age
              << " | GPA: "    << std::setw(4) << s.gpa
              << " | score: "  << std::setw(3) << s.score
              << "\n";
}

void printPoint(const Point3D& p) {
    std::cout << std::fixed << std::setprecision(3)
              << "  Point("
              << std::setw(9) << p.x << ", "
              << std::setw(9) << p.y << ", "
              << std::setw(9) << p.z << ")\n";
}

void printStudents(const Student* students, int count) {
    for (int i = 0; i < count; ++i) printStudent(students[i]);
}

void printPoints(const Point3D* points, int count) {
    for (int i = 0; i < count; ++i) printPoint(points[i]);
}

int main() {
    constexpr int INT_SIZE = 10;
    int intArr[INT_SIZE];
    fillIntArray(intArr, INT_SIZE, -50, 50);
    std::cout << "=== Integer array (" << INT_SIZE << " elements, range [-50, 50]) ===\n";
    printIntArray(intArr, INT_SIZE);
    std::cout << "\n";

    constexpr int DBL_SIZE = 8;
    double dblArr[DBL_SIZE];
    fillDoubleArray(dblArr, DBL_SIZE, 0.0, 100.0);
    std::cout << "=== Double array (" << DBL_SIZE << " elements, range [0.0, 100.0)) ===\n";
    printDoubleArray(dblArr, DBL_SIZE);
    std::cout << "\n";

    constexpr int STUDENT_COUNT = 5;
    Student students[STUDENT_COUNT];
    fillStudents(students, STUDENT_COUNT);
    std::cout << "=== Student structs (" << STUDENT_COUNT << " objects) ===\n";
    printStudents(students, STUDENT_COUNT);
    std::cout << "\n";

    constexpr int POINT_COUNT = 4;
    Point3D points[POINT_COUNT];
    fillPoints(points, POINT_COUNT);
    std::cout << "=== Point3D structs (" << POINT_COUNT << " objects, range [-100, 100]) ===\n";
    printPoints(points, POINT_COUNT);

    return 0;
}