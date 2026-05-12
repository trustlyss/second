#pragma once

struct Student {
    int    id;
    int    age;
    double gpa;    // grade point average (1.0 – 5.0)
    int    score;  // test score (0 – 100)
};

struct Point3D {
    double x;
    double y;
    double z;
};

void fillIntArray   (int*    arr, int size, int    minVal, int    maxVal);
void fillDoubleArray(double* arr, int size, double minVal, double maxVal);

void printIntArray   (const int*    arr, int size);
void printDoubleArray(const double* arr, int size);

void fillStudents(Student* students, int count);
void fillPoints  (Point3D* points,   int count);

void printStudent (const Student& s);
void printPoint   (const Point3D& p);

void printStudents(const Student* students, int count);
void printPoints  (const Point3D* points,   int count);