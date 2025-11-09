#include <vector>
using namespace std;

using ll = long long;
using ull = unsigned long long;

template <class T, class cmp = less<T>>
struct discretize {
    vector<T> vec;
    void build() {
        sort(vec.begin(), vec.end(), cmp());
        vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    }
    size_t operator[](const T &x) {
        return lower_bound(vec.begin(), vec.end(), x, cmp()) - vec.begin();
    }
};
