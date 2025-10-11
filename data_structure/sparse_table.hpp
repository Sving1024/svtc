#include <functional>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

template <class T, class cmp = less<T>>
struct sparse_table {
    vector<vector<T>> vec;
    sparse_table() {}
    template <class iter>
    sparse_table(iter begin, iter end) {
        ull sz = distance(begin, end);
        ull lg_sz = __lg(sz) + 1;
        vec.resize(lg_sz + 1);
        for (ull i = 0; i < lg_sz; i++) {
            vec[i].resize(sz);
        }
        copy(begin, end, vec[0].begin());
        for (ull i = 1; i < lg_sz; i++) {
            for (ull j = 0; j < sz; j++) {
                ull nxt = j + (1 << (i - 1));
                if (nxt >= sz) {
                    vec[i][j] = vec[i - 1][j];
                }
                else {
                    vec[i][j] = min(vec[i - 1][j], vec[i - 1][nxt], cmp());
                }
            }
        }
    }
    T query(ull l, ull r) const {
        ull sz = r - l;
        ull lg = __lg(sz);
        return min(vec[lg][l], vec[lg][r - (1 << lg)], cmp());
    }
};
