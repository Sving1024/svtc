#include <cmath>

using ld = long double;

namespace maths {
    ld sq(ld x) { return x * x; }

    struct point {
        ld x, y;
        point operator+(const point &b) const { return {x + b.x, y + b.y}; }
        point operator-(const point &b) const { return {x - b.x, y - b.y}; }
        point operator*(const ld &k) const { return {x * k, y * k}; }
        point operator/(const ld &k) const { return {x / k, y / k}; }
        point operator/=(const ld &k) { return *this = *this / k; }
        ld len() { return sqrt(sq(x) + sq(y)); }
    };

    ld dis(const point &a, const point &b) {
        return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
    }
} // namespace maths