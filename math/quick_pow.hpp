#include <string>

using ll = long long;
using ull = unsigned long long;

namespace maths {
    template <class T>
    T quick_pow(T a, ull b, T id = T()) {
        T ret = id;
        for (; b; b >>= 1, a = a * a) {
            if (b & 1) {
                ret = a * ret;
            }
        }
        return ret;
    }

    template <class T>
    T quick_pow(T a, const std::string &s, T id = T()) {
        T ret = id;
        for (size_t i = 0; i < s.size(); i++, a = a * a) {
            if (s[i] == '1') {
                ret = a * ret;
            }
        }
        return ret;
    }

} // namespace maths