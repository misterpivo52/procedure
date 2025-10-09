#include "bisection.h"
#include <math.h>

static double f(double x, double a, double b) {
    return a * x + b - x;
}

double bisection_search(double a, double b, double left, double right, double accuracy, int *iterations) {
    *iterations = 0;

    while (fabs(right - left) > accuracy) {
        double mid = (left + right) / 2.0;
        double f_left = f(left, a, b);
        double f_mid = f(mid, a, b);

        if (fabs(f_mid) < accuracy) {
            (*iterations)++;
            return mid;
        }

        if (f_left * f_mid < 0) {
            right = mid;
        } else {
            left = mid;
        }

        (*iterations)++;
    }

    return (left + right) / 2.0;
}