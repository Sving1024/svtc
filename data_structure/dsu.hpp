#include <vector>
using namespace std;

using ll = long long;
using ull = unsigned long long;

struct dsu {
    vector<ull> fa;
    dsu() {}
    void push_back() { fa.push_back(fa.size()); }
    void resize(ull sz) {
        while (fa.size() < sz) {
            push_back();
        }
    }
    ull find_root(ull p) {
        if (fa[p] == p) {
            return p;
        }
        else {
            return fa[p] = find_root(fa[p]);
        }
    }
    bool is_same(ull x, ull y) { return find_root(x) == find_root(y); }
    void merge(ull x, ull y) {
        ull rx = find_root(x), ry = find_root(y);
        if (rx != ry) {
            fa[rx] = ry;
        }
        return;
    }
};