#include <vector>

namespace ds {
    using std::vector;

    template <class T>
    struct adj_table {

        struct node {
            T val;
            size_t nxt;
        };

        static const size_t npos = static_cast<size_t>(-1);

        vector<size_t> head;
        vector<node> nd;

        adj_table(size_t n) : head(n, static_cast<size_t>(-1)), nd() {}

        adj_table() {}

        void insert(size_t pos, const T &_val) {
            nd.push_back(node{_val, head[pos]});
            head[pos] = nd.size() - 1;
        }

        size_t next_pos(size_t i) { return nd[i].nxt; }
    };
} // namespace ds
