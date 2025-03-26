#include "utils.hpp"

int gcd(int a, int b) {
    // std::abs is used to avoid negative numbers as the gcd is always positive even if the numbers are negative
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int modulo {a % b};
        a = b;
        b = modulo;
    }

    return a;
}

Fraction simplify(Fraction const& f) {
    int divisor = gcd(f.numerator, f.denominator);

    return Fraction(f.numerator / divisor, f.denominator / divisor);
}