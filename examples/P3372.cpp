#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using ll = long long;
using ull = unsigned long long;

namespace ds {
    template <class info_t, class tag_t,
              class merge_info_op = std::plus<info_t>,
              class apply_op = std::multiplies<void>,
              class merge_tag_op = std::plus<tag_t>>
    class lazy_segtree {
      public:
        const merge_info_op merge_info;
        const apply_op apply_to_info;
        const merge_tag_op merge_tag;
        const info_t id_info;
        const tag_t id_tag;
        const size_t npos = static_cast<size_t>(-1);

        struct node {
            info_t info;
            tag_t tg;

            size_t l, r;

            size_t mid() const { return (l + r) / 2; }
        };

        std::vector<node> t;

      private:
        size_t lc(const size_t &p) const { return 2 * p; }
        size_t rc(const size_t &p) const { return 2 * p + 1; }
        void update(size_t p) {
            t[p].info = merge_info(t[lc(p)].info, t[rc(p)].info);
            return;
        }

        void apply_to_node(size_t p, const tag_t &tag) {
            t[p].tg = merge_tag(tag, t[p].tg);
            t[p].info = apply_to_info(t[p].info, tag);
        }

        void spread(size_t p) {
            apply_to_node(lc(p), t[p].tg);
            apply_to_node(rc(p), t[p].tg);
            t[p].tg = id_tag;
            return;
        }

        void build(size_t l, size_t r, const std::vector<info_t> &init_val,
                   size_t p = 1) {
            t[p].l = l;
            t[p].r = r;
            t[p].info = id_info;
            t[p].tg = id_tag;
            if (l + 1 == r) {
                t[p].info = init_val[l];
                return;
            }
            size_t mid = t[p].mid();
            build(l, mid, init_val, lc(p));
            build(mid, r, init_val, rc(p));
            update(p);
            return;
        }

      public:
        lazy_segtree()
            : merge_info(), apply_to_info(), merge_tag(), id_info(), id_tag(),
              t() {}

        lazy_segtree(size_t n,
                     const merge_info_op &_merge_info = merge_info_op(),
                     const apply_op &_apply = apply_op(),
                     const merge_tag_op &_merge_tag = merge_tag_op(),
                     const info_t &_info_id = info_t(),
                     const tag_t &_tag_id = tag_t())
            : merge_info(_merge_info), apply_to_info(_apply),
              merge_tag(_merge_tag), id_info(_info_id), id_tag(_tag_id),
              t(n * 4) {
            build(0, n, std::vector<info_t>(n, id_info));
        }

        template <class iter>
        lazy_segtree(iter iter_begin, iter iter_end,
                     const merge_info_op &_merge_info = merge_info_op(),
                     const apply_op &_apply = apply_op(),
                     const merge_tag_op &_merge_tag = merge_tag_op(),
                     const info_t &_info_id = info_t(),
                     const tag_t &_tag_id = tag_t())
            : merge_info(_merge_info), apply_to_info(_apply),
              merge_tag(_merge_tag), id_info(_info_id), id_tag(_tag_id),
              t(std::distance(iter_begin, iter_end) * 4) {
            size_t n = std::distance(iter_begin, iter_end);
            build(0, n, std::vector<info_t>(iter_begin, iter_end));
        }

        void apply(size_t l, size_t r, const tag_t &tag, size_t p = 1) {
            if (l <= t[p].l && t[p].r <= r) {
                apply_to_node(p, tag);
                return;
            }
            size_t mid = t[p].mid();
            spread(p);
            if (l < mid) {
                apply(l, r, tag, lc(p));
            }
            if (mid < r) {
                apply(l, r, tag, rc(p));
            }
            update(p);
            return;
        }

        info_t query(size_t l, size_t r, size_t p = 1) {
            if (l <= t[p].l && t[p].r <= r) {
                return t[p].info;
            }
            size_t mid = t[p].mid();
            spread(p);
            info_t ret = id_info;
            if (l < mid) {
                ret = merge_info(query(l, r, lc(p)), ret);
            }
            if (mid < r) {
                ret = merge_info(ret, query(l, r, rc(p)));
            }
            update(p);
            return ret;
        }

        void set(size_t pos, const info_t &info, size_t p = 1) {
            if (t[p].l + 1 == t[p].r) {
                t[p].info = info;
                return;
            }
            size_t mid = t[p].mid();
            spread(p);
            if (pos < mid) {
                set(pos, info, lc(p));
            }
            else {
                set(pos, info, rc(p));
            }
            update(p);
            return;
        }
    };
} // namespace ds

namespace solve {
    struct tag {
        ll val;
        tag() : val(0) {}
        tag(ll _val) : val(_val) {}
        tag operator+(const tag &rhs) const { return {val + rhs.val}; }
    };
    struct info {
        ll val;
        size_t len;
        info() : val(0), len(0) {}
        info(ll _val, size_t _len) : val(_val), len(_len) {}
        info operator+(const info &rhs) const {
            return {val + rhs.val, len + rhs.len};
        }
        info operator*(const tag &tg) const {
            return {val + tg.val * (ll)len, len};
        }
    };

    void solve() {
        size_t n, q;
        std::cin >> n >> q;
        std::vector<ll> v(n);
        std::copy_n(std::istream_iterator<ll>(std::cin), n, v.begin());
        std::vector<info> new_v(n);
        for (size_t i = 0; i < n; i++) {
            new_v[i].val = v[i];
            new_v[i].len = 1;
        }
        ds::lazy_segtree<info, tag> sgt(new_v.begin(), new_v.end());
        while (q--) {
            size_t op;
            std::cin >> op;
            if (op == 1) {
                size_t x, y;
                ll k;
                std::cin >> x >> y >> k;
                x--;
                sgt.apply(x, y, {k});
            }
            else {
                size_t x, y;
                std::cin >> x >> y;
                x--;
                std::cout << sgt.query(x, y).val << "\n";
            }
        }
        return;
    }
}; // namespace solve

int main() {
    solve::solve();
    std::cout << std::flush;
    return 0;
}
