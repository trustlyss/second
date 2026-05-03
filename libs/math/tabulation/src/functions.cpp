#include "functions.hpp"
#include <cmath>
using namespace std;

namespace math {

    double func1D(double x) {
        if (x < 0) {
            return x - 2;
        } else if (x <= 3) {
            return fabs(x - 3) / (4 + x);
        } else {
            return -x + 3;
        }
    }

    double func2D(double x, double y) {
        return exp(x - y) * cos(x + y);
    }

}
