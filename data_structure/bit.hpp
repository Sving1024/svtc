#include <array>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

size_t lowbit(size_t x) { return x & -x; }

template <class T, size_t N>
struct bit {
    array<T, N> t;
    void add(size_t p, T val) {
        for (; p < N; p += lowbit(p)) {
            t[p] += val;
        }
        return;
    }
    T query(size_t p) const {
        if (p < 0) {
            return 0;
        }
        T ret = 0;
        for (; p; p -= lowbit(p)) {
            ret += t[p];
        }
        return ret;
    }
    T query(size_t l, size_t r) const { return query(r) - query(l - 1); }
};

template <class T, size_t N>
struct bit_with_coef {
  private:
    void add(size_t pos, T val) {
        // 这个函数返回的是前缀和。
        // 并不是单点的值。
        b.add(pos, val);
        c.add(pos, val * sum_coef[pos - 1]);
        return;
    }
    ll query(size_t r) const { return sum_coef[r] * b.query(r) - c.query(r); }

  public:
    array<T, N> sum_coef;
    bit<T, N> b, c;
    void build(const vector<T> &vec) {
        copy(vec.begin(), vec.end(), sum_coef.begin());
        for (size_t i = 1; i < vec.size(); i++) {
            sum_coef[i] += sum_coef[i - 1];
        }
        return;
    }
    void add(size_t l, size_t r, T val) {
        add(l, val);
        add(r + 1, -val);
        return;
    }
    ll query(size_t l, size_t r) const { return query(r) - query(l - 1); }
};
