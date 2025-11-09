using ll = long long;
using ull = unsigned long long;

namespace maths {
    template <ull mod, class int_type = ll>
    class modular {
      private:
        using uint_type = unsigned int_type;

      public:
        uint_type x;

      private:
        void norm() {
            if (x >= mod) {
                x -= mod;
            }
        }

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
        modular(uint_type _x) { x = _x % MOD; }
        modular operator+(const modular &b) const {
            modular ret;
            ret.x = x + b.x;
            ret.norm();
            return ret;
        }
        modular operator-(const modular &b) const {
            modular ret;
            ret.x = x + mod - b.x;
            ret.norm();
            return ret;
        }
        modular operator-() {
            modular ret;
            ret.x = mod - x;
            return ret;
        }
        modular operator-=(const modular &b) { return *this = *this - b; }
        modular operator*(const modular &b) const { return modular(x * b.x); }
        modular operator+=(const modular &b) { return *this = *this + b; }
        modular operator*=(const modular &b) { return *this = *this * b; }
        bool operator==(const modular &b) const { return x == b.x; }
    };
} // namespace maths