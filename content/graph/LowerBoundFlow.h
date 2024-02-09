/**
 * Date: 2024-02-08
 * Source:
 * Some NWERC solution
 * Description: Dinic to run flows, has a lower bound option too.
 */
template <typename C, typename R = C, bool lb = false> struct dinic {
  typedef C flow_type;
  typedef R result_type;
  static const flow_type oo = std::numeric_limits<flow_type>::max();
  struct edge {
    int src, dst, rev;
    flow_type cap, flow;
    edge(int src, int dst, int rev, flow_type cap, flow_type flow)
        : src(src), dst(dst), rev(rev), cap(cap), flow(flow) {}
  };
  dinic(int n)
      : adj(n + 2 * lb), que(n + 2 * lb), level(n + 2 * lb),
        edge_pos(n + 2 * lb) {}
  int add_edge(int src, int dst, flow_type cap,
               flow_type rcap = 0) { // if lb rcap is low
    adj[src].emplace_back(src, dst, (int)adj[dst].size(), cap, lb ? rcap : 0);
    if (src == dst)
      adj[src].back().rev++;
    adj[dst].emplace_back(dst, src, (int)adj[src].size() - 1, lb ? 0 : rcap, 0);
    return (int)adj[src].size() - 1 - (src == dst);
  }
  inline bool side_of_S(int u) { return level[u] == -1; }
  result_type max_flow(int source, int sink) {
    result_type flow = 0;
    while (true) {
      int front = 0, back = 0;
      std::fill(level.begin(), level.end(), -1);
      for (level[que[back++] = sink] = 0; front < back && level[source] == -1;
           ++front) {
        int u = que[front];
        for (const edge &e : adj[u])
          if (level[e.dst] == -1 && rev(e).flow < rev(e).cap)
            level[que[back++] = e.dst] = 1 + level[u];
      }
      if (level[source] == -1)
        break;
      std::fill(edge_pos.begin(), edge_pos.end(), 0);
      std::function<flow_type(int, flow_type)> find_path = [&](int from,
                                                               flow_type res) {
        if (from == sink)
          return res;
        for (int &ept = edge_pos[from]; ept < (int)adj[from].size(); ++ept) {
          edge &e = adj[from][ept];
          if (e.flow == e.cap || level[e.dst] + 1 != level[from])
            continue;
          flow_type push = find_path(e.dst, std::min(res, e.cap - e.flow));
          if (push > 0) {
            e.flow += push;
            rev(e).flow -= push;
            if (e.flow == e.cap)
              ++ept;
            return push;
          }
        }
        return static_cast<flow_type>(0);
      };
      for (flow_type f; (f = find_path(source, oo)) > 0;)
        flow += f;
    }
    return flow;
  }
  result_type max_flow_lb(int source, int sink) {
    int n = adj.size() - 2;
    vector<flow_type> delta(n + 2);
    for (int u = 0; u < n; ++u)
      for (auto &e : adj[u]) {
        delta[u] -= e.flow;
        delta[e.dst] += e.flow;
      }
    result_type sum = 0;
    int s = n, t = n + 1;
    for (int u = 0; u < n; ++u) {
      if (delta[u] > 0) {
        add_edge(s, u, delta[u], 0);
        sum += delta[u];
      } else if (delta[u] < 0)
        add_edge(u, t, -delta[u], 0);
    }
    add_edge(sink, source, oo, 0);
    if (max_flow(s, t) != sum)
      return -1; // no solution
    result_type flow = adj[sink].back().flow;
    adj[sink].pop_back();
    adj[source].pop_back();
    return flow + max_flow(source, sink);
  }
  std::vector<std::vector<edge>> adj;

private:
  std::vector<int> que;
  std::vector<int> level;
  std::vector<int> edge_pos;
  inline edge &rev(const edge &e) { return adj[e.dst][e.rev]; }
};