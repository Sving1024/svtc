#include <vector>

using ll = long long;
using ull = unsigned long long;

template <class T, class cmp = std::less<T>>
struct discretize {
    std::vector<T> vec;
    void build() {
        sort(vec.begin(), vec.end(), cmp());
        vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    }
    size_t operator[](const T &x) {
        return lower_bound(vec.begin(), vec.end(), x, cmp()) - vec.begin();
    }
};
