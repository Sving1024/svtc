#include <functional>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

template <class T, class binary_op = plus<T>, class inv_op = minus<T>>
struct sum_prefix {
    vector<T> vec;
    sum_prefix(const vector<T> &_vec) {
        vec = _vec;
        for (ull i = 0; i < vec.size() - 1; i++) {
            vec[i + 1] += vec[i];
        }
        return;
    }
    template <class iter>
    sum_prefix(iter begin, iter end) {
        vec.resize(distance(begin, end));
        copy(begin, end, vec.begin());
        for (ull i = 0; i < vec.size() - 1; i++) {
            vec[i + 1] = binary_op()(vec[i + 1], vec[i]);
        }
    }
    T query(ull l, ull r) const {
        return inv_op()(vec[r - 1], (l == 0 ? 0 : vec[l - 1]));
    }
};
