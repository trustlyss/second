#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <limits>
#include "lab07.hpp"

int main() {
    const double a  = -4.0, b  =  4.0, h  = 0.1;
    const double x1 = -3.0, x2 =  3.0, hx = 0.25;
    const double y1 =  1.0, y2 =  2.0, hy = 0.15;

    std::cout << std::fixed << std::setprecision(6);

    // --- Table 1: y = f(x) ---
    std::cout << "=== Table 1: y = f(x), x in [" << a << ", " << b << "], h = " << h << " ===\n";
    std::cout << std::setw(12) << "x" << std::setw(15) << "y = f(x)" << "\n";
    std::cout << std::string(27, '-') << "\n";

    double y_max = -std::numeric_limits<double>::infinity();
    double y_min =  std::numeric_limits<double>::infinity();
    double x_at_max = a, x_at_min = a;

    int n1 = static_cast<int>(std::round((b - a) / h)) + 1;
    for (int i = 0; i < n1; ++i) {
        double x = a + i * h;
        double y = f_one(x);
        std::cout << std::setw(12) << x << std::setw(15) << y << "\n";
        if (y > y_max) { y_max = y; x_at_max = x; }
        if (y < y_min) { y_min = y; x_at_min = x; }
    }
    std::cout << "\nMax y = " << y_max << "  at x = " << x_at_max << "\n";
    std::cout << "Min y = " << y_min << "  at x = " << x_at_min << "\n";

    // --- Table 2: z = f(x, y) ---
    std::cout << "\n=== Table 2: z = f(x,y) = sqrt(x*(y+1))/(x-y) ===\n";
    std::cout << "x in [" << x1 << ", " << x2 << "], hx = " << hx
              << " | y in [" << y1 << ", " << y2 << "], hy = " << hy << "\n\n";

    int nx = static_cast<int>(std::round((x2 - x1) / hx)) + 1;
    int ny = static_cast<int>(std::round((y2 - y1) / hy)) + 1;

    double z_max = -std::numeric_limits<double>::infinity();
    double z_min =  std::numeric_limits<double>::infinity();
    double zx_max, zy_max, zx_min, zy_min;

    std::cout << std::setw(10) << "x \\ y";
    for (int j = 0; j < ny; ++j)
        std::cout << std::setw(12) << y1 + j * hy;
    std::cout << "\n" << std::string(10 + ny * 12, '-') << "\n";

    for (int i = 0; i < nx; ++i) {
        double x = x1 + i * hx;
        std::cout << std::setw(10) << x;
        for (int j = 0; j < ny; ++j) {
            double y = y1 + j * hy;
            try {
                double z = f_two(x, y);
                std::cout << std::setw(12) << z;
                if (z > z_max) { z_max = z; zx_max = x; zy_max = y; }
                if (z < z_min) { z_min = z; zx_min = x; zy_min = y; }
            } catch (...) {
                std::cout << std::setw(12) << "undef";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nMax z = " << z_max << "  at x = " << zx_max << ", y = " << zy_max << "\n";
    std::cout << "Min z = " << z_min << "  at x = " << zx_min << ", y = " << zy_min << "\n";

    return 0;
}