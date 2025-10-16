#include <cassert>
using namespace std;

using ll = long long;
using ull = unsigned long long;

struct dynamic_modular {
    ll x;
    ull mod;
    dynamic_modular() : x(0), mod(0) {}
    dynamic_modular(ull _x, ull _mod) : x(_x), mod(_mod) {
        x %= mod;
        if (x < 0) {
            x += mod;
        }
    }
    dynamic_modular operator+(const dynamic_modular &b) const {
        assert(mod == b.mod);
        return dynamic_modular(x + b.x, mod);
    }
    template <class T>
    dynamic_modular operator+(const T &b) const {
        return dynamic_modular(x + b, mod);
    }
    dynamic_modular operator*(const dynamic_modular &b) {
        assert(mod == b.mod);
        return dynamic_modular(x * b.x, mod);
    }
    template <class T>
    dynamic_modular operator*(const T &b) const {
        return dynamic_modular(x * b, mod);
    }
    dynamic_modular operator-(const dynamic_modular &b) const {
        assert(mod == b.mod);
        return dynamic_modular(x * b.x, mod);
    }
    template <class T>
    dynamic_modular operator-(const T &b) const {
        return dynamic_modular(x * b, mod);
    }
    template <class T>
    dynamic_modular operator+=(const T &b) {
        assert(mod == b.mod);
        return *this = *this + b;
    }
    template <class T>
    dynamic_modular operator*=(const T &b) {
        assert(mod == b.mod);
        return *this = *this * b;
    }
    template <class T>
    dynamic_modular operator-=(const T &b) {
        assert(mod == b.mod);
        return *this = *this - b;
    }
    void setmod(ull _mod) {
        mod = _mod;
        x %= mod;
        if (x < 0) {
            x += mod;
        }
    }
};
