#include <array>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

ull lowbit(ull x) { return x & -x; }

template <class T, ull N>
struct bit {
    array<T, N> t;
    void add(ull p, T val) {
        for (; p < N; p += lowbit(p)) {
            t[p] += val;
        }
        return;
    }
    T query(ull p) {
        if (p < 0) {
            return 0;
        }
        T ret = 0;
        for (; p; p -= lowbit(p)) {
            ret += t[p];
        }
        return ret;
    }
    T query(ull l, ull r) { return query(r) - query(l - 1); }
};

template <class T, ull N>
struct bit_with_coef {
  private:
    void add(ull pos, ull val) {
        // 这个函数返回的是前缀和。
        // 并不是单点的值。
        b.add(pos, val);
        c.add(pos, val * sum_coef[pos - 1]);
        return;
    }
    ll query(ull r) const { return sum_coef[r] * b.query(r) - c.query(r); }

  public:
    array<T, N> sum_coef;
    bit<T, N> b, c;
    void build(const vector<T> &vec) {
        copy(vec.begin(), vec.end(), sum_coef.begin());
        for (ull i = 1; i < vec.size(); i++) {
            sum_coef[i] += sum_coef[i - 1];
        }
        return;
    }
    void add(ull l, ull r, ull val) {
        add(l, val);
        add(r + 1, -val);
        return;
    }
    ll query(ull l, ull r) const { return query(r) - query(l - 1); }
};
