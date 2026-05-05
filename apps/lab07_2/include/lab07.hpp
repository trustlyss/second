#pragma once
#include <cmath>
#include <stdexcept>

double f_one(double x) {
    if (x < 0)
        return -x * x + 1.0 / x;
    else if (x < 3)
        return std::sqrt(x * x + 1);
    else
        return x - 3.0;
}

double f_two(double x, double y) {
    double num = x * (y + 1);
    if (num < 0)
        throw std::domain_error("sqrt of negative");
    if (std::abs(x - y) < 1e-12)
        throw std::domain_error("division by zero");
    return std::sqrt(num) / (x - y);
}