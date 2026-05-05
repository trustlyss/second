#pragma once
#include <cmath>

double f_exact(double x) {
    return M_PI * x / 4.0;
}

double series_n_terms(double x, int N) {
    double sum = 0.0;
    for (int n = 0; n <= N; ++n) {
        int sign = (n + 1) % 2 == 0 ? -1 : 1;
        double term = sign * std::sin((2 * n + 1) * x) / ((2 * n + 1) * (2 * n + 1));
        sum += term;
    }
    return sum;
}

double series_eps(double x, double eps, int& out_count) {
    double sum = 0.0;
    int n = 0;
    while (true) {
        int sign = (n + 1) % 2 == 0 ? -1 : 1;
        double term = sign * std::sin((2 * n + 1) * x) / ((2 * n + 1) * (2 * n + 1));
        sum += term;
        ++n;
        int next_sign = (n + 1) % 2 == 0 ? -1 : 1;
        double next_term = std::abs(next_sign * std::sin((2 * n + 1) * x)
                                    / ((2 * n + 1) * (2 * n + 1)));
        if (next_term < eps) break;
        if (n > 100000) break;
    }
    out_count = n;
    return sum;
}