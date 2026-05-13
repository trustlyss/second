#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <stdexcept>

struct Car {
    std::string brand;
    int         year;
    double      maxSpeed;
    double      price;
};

struct Student {
    std::string name;
    int         age;
    double      gpa;
};

template <typename T>
T euclideanNorm(const std::vector<T>& arr) {
    T sumSq = std::accumulate(arr.begin(), arr.end(), T(0),
        [](T acc, T val) { return acc + val * val; });
    return std::sqrt(sumSq);
}

template <typename T>
std::vector<T> divideByMax(const std::vector<T>& arr) {
    T maxVal = *std::max_element(arr.begin(), arr.end());
    if (maxVal == T(0)) throw std::runtime_error("Max element is zero");
    std::vector<T> result(arr.size());
    std::transform(arr.begin(), arr.end(), result.begin(),
        [maxVal](T val) { return val / maxVal; });
    return result;
}

template <typename T>
std::vector<T> multiplyByMin(const std::vector<T>& arr) {
    T minVal = *std::min_element(arr.begin(), arr.end());
    std::vector<T> result(arr.size());
    std::transform(arr.begin(), arr.end(), result.begin(),
        [minVal](T val) { return val * minVal; });
    return result;
}

Car fastestCar(const std::vector<Car>& cars);
Car mostExpensiveCar(const std::vector<Car>& cars);

Student topStudent(const std::vector<Student>& students);

std::vector<double>  randomDoubleVec(int size, double minVal, double maxVal);
std::vector<Car>     randomCars(int count);
std::vector<Student> randomStudents(int count);