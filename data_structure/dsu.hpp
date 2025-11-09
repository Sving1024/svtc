#include <vector>
using namespace std;

using ll = long long;
using ull = unsigned long long;

namespace data_structure {
    struct dsu {
        vector<size_t> fa;
        dsu() {}
        void push_back() { fa.push_back(fa.size()); }
        void resize(size_t sz) {
            while (fa.size() < sz) {
                push_back();
            }
        }
        size_t find_root(size_t p) {
            if (fa[p] == p) {
                return p;
            }
            else {
                return fa[p] = find_root(fa[p]);
            }
        }
        bool is_same(size_t x, size_t y) { return find_root(x) == find_root(y); }
        void merge(size_t x, size_t y) {
            size_t rx = find_root(x), ry = find_root(y);
            if (rx != ry) {
                fa[rx] = ry;
            }
            return;
        }
    };
} // namespace data_structure
