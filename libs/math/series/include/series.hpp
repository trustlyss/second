#pragma once
#include <cmath>

namespace series {

    struct EpsResult {
        double value;
        int terms;
    };

    double exactValue(double x);
    double sumByTerms(double x, int n);
    EpsResult sumByEps(double x, double eps);

}
