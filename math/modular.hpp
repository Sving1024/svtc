using ll = long long;
using ull = unsigned long long;

template <ll MOD, class INT_TYPE = ll>
struct modular {
    INT_TYPE x;
    modular() : x(0) {}
    modular(INT_TYPE _x) {
        x = _x % MOD;
        if (x < 0) {
            x += MOD;
        }
        return;
    }
    modular operator+(const modular &b) const { return modular(x + b.x); }
    modular operator*(const modular &b) const { return modular(x * b.x); }
    modular operator+=(const modular &b) { return *this = *this + b; }
    modular operator*=(const modular &b) { return *this = *this * b; }
    modular operator-(const modular &b) const { return modular(x - b.x); }
    modular operator-=(const modular &b) { return *this = *this - b; }
    modular operator-() { return modular(-x); }
    bool operator==(const modular &b) const { return x == b.x; }
};
