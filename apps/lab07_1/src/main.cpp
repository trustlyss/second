#include <iostream>
#include <iomanip>
#include <cmath>
#include "bits.hpp"

int main() {
    const double a    = 0.0;
    const double b    = M_PI / 2.0;
    const int    k    = 11;
    const int    N    = 10;
    const double eps  = 0.0001;

    double h = (b - a) / (k - 1);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "=== Variant 8: S = sum(-1)^(n+1) * sin((2n+1)*x) / (2n+1)^2 ===\n";
    std::cout << "Segment [0, pi/2], step h = " << h << "\n\n";

    std::cout << "--- Case 1: n = " << N << " terms ---\n";
    std::cout << std::setw(10) << "x"
              << std::setw(15) << "S (series,n=10)"
              << std::setw(15) << "f(x)=pi*x/4"
              << std::setw(15) << "|error|"
              << "\n";
    std::cout << std::string(55, '-') << "\n";

    for (int i = 0; i < k; ++i) {
        double x     = a + i * h;
        double s_val = series_n_terms(x, N);
        double exact = f_exact(x);
        double err   = std::abs(s_val - exact);
        std::cout << std::setw(10) << x
                  << std::setw(15) << s_val
                  << std::setw(15) << exact
                  << std::setw(15) << err
                  << "\n";
    }

    std::cout << "\n--- Case 2: precision eps = " << eps << " ---\n";
    std::cout << std::setw(10) << "x"
              << std::setw(15) << "S (series,eps)"
              << std::setw(10) << "terms"
              << std::setw(15) << "f(x)=pi*x/4"
              << std::setw(15) << "|error|"
              << "\n";
    std::cout << std::string(65, '-') << "\n";

    for (int i = 0; i < k; ++i) {
        double x = a + i * h;
        int    cnt;
        double s_val = series_eps(x, eps, cnt);
        double exact = f_exact(x);
        double err   = std::abs(s_val - exact);
        std::cout << std::setw(10) << x
                  << std::setw(15) << s_val
                  << std::setw(10) << cnt
                  << std::setw(15) << exact
                  << std::setw(15) << err
                  << "\n";
    }

    return 0;
}