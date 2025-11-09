#include <functional>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

namespace data_structure {
    template <class T, class binary_op = plus<T>, class inv_op = minus<T>>
    struct sum_prefix {
        const size_t npos = -1;
        vector<T> vec;
        const T unit_element;
        sum_prefix(const vector<T> &_vec, T _unit = T()) : unit_element(_unit) {
            vec = _vec;
            for (size_t i = 0; i < vec.size() - 1; i++) {
                vec[i + 1] += vec[i];
            }
            return;
        }
        template <class iter>
        sum_prefix(iter begin, iter end, T _unit = T()) : unit_element(_unit) {
            vec.resize(distance(begin, end));
            copy(begin, end, vec.begin());
            for (size_t i = 0; i < vec.size() - 1; i++) {
                vec[i + 1] = binary_op()(vec[i + 1], vec[i]);
            }
        }
        T query(size_t l, size_t r) const {
            return inv_op()(vec[r - 1], (l == 0 ? unit_element : vec[l - 1]));
        }
        T query(size_t pos) {
            return pos - 1 == npos ? unit_element : vec[pos - 1];
        }
    };
} // namespace data_structure