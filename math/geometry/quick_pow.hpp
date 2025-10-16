using ll = long long;
using ull = unsigned long long;

template <class T>
T quick_pow(T a, ull b, T id = T()) {
    T ret = id;
    for (; b; b >>= 1, a = a * a) {
        if (b & 1) {
            ret *= a;
        }
    }
    return ret;
}
