#include <iostream>

using ll = long long;
using ull = unsigned long long;

namespace maths {
    template <ull mod, class int_type = ll, class uint_type = ull>
    class modular {
      private:
        uint_type x;
        void norm() { x -= mod * (x >= mod); }

      public:
        modular() : x(0) {}
        modular(int_type _x) {
            if (x < 0) {
                x = _x % (int_type)mod + (int_type)mod;
            }
            else {
                x = _x % mod;
            }
            norm();
            return;
        }
        friend modular operator+(const modular &lhs, const modular &rhs) {
            modular ret;
            ret.x = lhs.x + rhs.x;
            ret.norm();
            return ret;
        }
        friend modular operator-(const modular &lhs, const modular &rhs) {
            modular ret;
            ret.x = lhs.x + mod - rhs.x;
            ret.norm();
            return ret;
        }
        friend modular operator*(const modular &lhs, const modular &rhs) {
            return modular(lhs.x * rhs.x);
        }
        modular operator-() const {
            modular ret;
            ret.x = mod - x;
            return ret;
        }
        modular operator-=(const modular &b) { return *this = *this - b; }
        modular operator+=(const modular &b) { return *this = *this + b; }
        modular operator*=(const modular &b) { return *this = *this * b; }
        bool operator==(const modular &b) const { return x == b.x; }
        uint_type val() const { return x; }
        friend std::istream &operator>>(std::istream &is, modular &rhs) {
            is >> rhs.x;
            rhs.x %= mod;
            return is;
        }
        friend std::ostream &operator<<(std::ostream &os, const modular &rhs) {
            os << rhs.val();
            return os;
        }
    };
} // namespace maths