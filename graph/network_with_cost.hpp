#include <vector>
#include <queue>

namespace graph {
    template <typename result_type, typename cost_type>
    struct network_with_cost {
        struct edge {
            size_t src, dest;
            result_type vol;
            cost_type cost;
        };

        ds::adj_table<edge> g;

        size_t s, t;
        size_t n;

        std::vector<cost_type> dis;
        std::vector<size_t> prev_node;

        constexpr static const size_t npos = static_cast<size_t>(-1);

        bool spfa() {
            std::fill(dis.begin(), dis.end(), numbers::inf<uint>());
            std::fill(prev_node.begin(), prev_node.end(),
                      network_with_cost<result_type, cost_type>::npos);

            std::queue<size_t> q;

            q.push(s);
            dis[s] = 0;

            while (!q.empty()) {
                auto f = q.front();
                q.pop();

                for (size_t i = g.head[f]; i != ds::adj_table<edge>::npos;
                     i = g.next_pos(i)) {
                    const edge &e = g.nd[i].val;
                    if (dis[e.dest] > dis[f] + e.cost && e.vol != 0) {
                        dis[e.dest] = dis[f] + e.cost;
                        prev_node[e.dest] = i;
                        q.push(e.dest);
                    }
                }
            }

            return dis[t] != numbers::inf<cost_type>();
        }

        struct flow {
            result_type vol;
            cost_type cost;
        };

        flow ek() {
            flow ret{0, 0};
            while (spfa()) {
                result_type r = numbers::inf<result_type>();
                cost_type c = 0;
                {
                    size_t cur = t;
                    while (cur != s) {
                        const auto &e = g.nd[prev_node[cur]].val;
                        c += e.cost;
                        r = std::min(r, e.vol);
                        cur = e.src;
                    }
                }
                ret.cost += r * c;
                ret.vol += r;
                {
                    size_t cur = t;
                    while (cur != s) {
                        const auto &e = g.nd[prev_node[cur]].val;
                        g.nd[prev_node[cur]].val.vol -= r;
                        g.nd[prev_node[cur] ^ 1].val.vol += r;
                        cur = e.src;
                    }
                }
            }
            return ret;
        }

        network_with_cost(size_t _n, size_t _s, size_t _t)
            : g(_n), s(_s), t(_t), n(_n), dis(_n), prev_node(_n) {}

        void add_edge(size_t src, size_t dest, result_type vol,
                      cost_type cost) {
            g.insert(src, {src, dest, vol, cost});
            g.insert(dest, {dest, src, 0, -cost});
        }
    };

    template <typename result_type, typename cost_type>
    const size_t network_with_cost<result_type, cost_type>::npos;
} // namespace graph
