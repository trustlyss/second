#include "series.hpp"
using namespace std;

namespace series {

    const double LN3 = log(3.0);

    double exactValue(double x) {
        return pow(3.0, x);
    }

    double sumByTerms(double x, int n) {
        double sum = 1.0;
        double term = 1.0;
        for (int i = 1; i <= n; i++) {
            term *= (x * LN3) / i;
            sum += term;
        }
        return sum;
    }

    EpsResult sumByEps(double x, double eps) {
        double sum = 1.0;
        double term = 1.0;
        int n = 1;
        while (fabs(term) >= eps) {
            term *= (x * LN3) / n;
            sum += term;
            n++;
        }
        return {sum, n - 1};
    }

}
