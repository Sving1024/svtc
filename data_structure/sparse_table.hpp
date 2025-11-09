#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

namespace data_structure {
    namespace functor {
        template <class T, class cmp = less<T>>
        struct min_element {
            cmp compare;
            min_element() : compare() {}
            min_element(cmp c) : compare(c) {}
            T operator(const T &a, const T &b) const {
                return std::min(a, b, compare);
            }
        };
    } // namespace functor

    template <class T, class binary_op = functor::min_element<T>>
    struct sparse_table {
        vector<vector<T>> vec;
        binary_op op;
        sparse_table() : vec(), op() {}
        template <class iter>
        sparse_table(iter begin, iter end, binary_op _op = binary_op())
            : op(_op) {
            size_t sz = distance(begin, end);
            size_t lg_sz = __lg(sz) + 1;
            vec.resize(lg_sz + 1);
            for (size_t i = 0; i < lg_sz; i++) {
                vec[i].resize(sz);
            }
            copy(begin, end, vec[0].begin());
            for (size_t i = 1; i < lg_sz; i++) {
                for (size_t j = 0; j < sz; j++) {
                    size_t nxt = j + (1 << (i - 1));
                    if (nxt >= sz) {
                        vec[i][j] = vec[i - 1][j];
                    }
                    else {
                        vec[i][j] = op(vec[i - 1][j], vec[i - 1][nxt]);
                    }
                }
            }
        }
        T query(size_t l, size_t r) const {
            size_t sz = r - l;
            size_t lg = __lg(sz);
            return op(vec[lg][l], vec[lg][r - (1 << lg)]);
        }
    };
} // namespace data_structure