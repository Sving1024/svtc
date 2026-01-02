#include <queue>
#include <vector>
#include "data_structure/adj_table.hpp"
#include "math/numbers.hpp"

namespace graph {
    template <typename result_type>
    struct network {
        struct edge {
            size_t src, dest;
            result_type vol;
        };

        ds::adj_table<edge> g;

        size_t s, t;
        size_t n;

        std::vector<uint> dis;
        std::vector<size_t> cur;

        bool bfs() {
            std::fill(dis.begin(), dis.end(), numbers::inf<uint>());
            std::vector<bool> vis(n);

            std::queue<size_t> q;

            q.push(s);
            vis[s] = true;
            dis[s] = 0;

            while (!q.empty()) {
                auto f = q.front();
                q.pop();

                for (size_t i = g.head[f]; i != ds::adj_table<edge>::npos;
                     i = g.next_pos(i)) {
                    const edge &e = g.nd[i].val;
                    if (!vis[e.dest] && e.vol != 0) {
                        dis[e.dest] = dis[f] + 1;
                        vis[e.dest] = true;
                        q.push(e.dest);
                    }
                }
            }

            cur = g.head;

            return dis[t] != numbers::inf<uint>();
        }

        result_type dfs(size_t p, result_type max_flow) {
            if (p == t) {
                return max_flow;
            }

            result_type final_flow = 0;
            for (; cur[p] != ds::adj_table<edge>::npos; cur[p] = g.next_pos(cur[p])) {
                const auto &i = cur[p];
                const edge &e = g.nd[i].val;

                if (dis[e.dest] != dis[p] + 1) {
                    continue;
                }

                auto r = dfs(e.dest, std::min(e.vol, max_flow));
                g.nd[i].val.vol -= r;
                g.nd[i ^ 1].val.vol += r;
                final_flow += r;
                max_flow -= r;

                if (!max_flow) {
                    break;
                }
            }

            return final_flow;
        }

        result_type dinic() {
            result_type r = 0;
            while (bfs()) {
                r += dfs(s, numbers::inf<result_type>());
            }
            return r;
        }

        network(size_t _n, size_t _s, size_t _t)
            : g(_n), s(_s), t(_t), n(_n), dis(_n), cur(_n) {}

        void add_edge(size_t src, size_t dest, result_type vol) {
            g.insert(src, {src, dest, vol});
            g.insert(dest, {dest, src, 0});
        }
    };

} // namespace graph
