/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: $O(F E \log(V))$ where F is max flow. $O(VE)$ for setpi.
 */
// #include <bits/extc++.h> /// include-line, keep-include
const int64_t INF = numeric_limits<int64_t>::max() / 4;
struct MCMF {
  struct edge {
    int from, to, rev;
    int64_t cap, cost, flow;
  };
  int N;
  vector<vector<edge>> ed;
  vector<int> seen;
  vector<int64_t> dist, pi;
  vector<edge*> par;
  MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}
  void addEdge(int from, int to, int64_t cap, int64_t cost) {
    if (from == to) return;
    ed[from].push_back(edge{from, to, (int)(ed[to]).size(), cap, cost, 0});
    ed[to].push_back(edge{to, from, (int)(ed[from]).size() - 1, 0, -cost, 0});
  }
  void path(int s) {
    fill(begin(seen), end(seen), 0);
    fill(begin(dist), end(dist), INF);
    dist[s] = 0;
    int64_t di;
    __gnu_pbds::priority_queue<pair<int64_t, int>> q;
    vector<decltype(q)::point_iterator> its(N);
    q.push({0, s});
    while (!q.empty()) {
      s = q.top().second;
      q.pop();
      seen[s] = 1;
      di = dist[s] + pi[s];
      for (edge& e : ed[s])
        if (!seen[e.to]) {
          int64_t val = di - pi[e.to] + e.cost;
          if (e.cap - e.flow > 0 && val < dist[e.to]) {
            dist[e.to] = val;
            par[e.to] = &e;
            if (its[e.to] == q.end())
              its[e.to] = q.push({-dist[e.to], e.to});
            else
              q.modify(its[e.to], {-dist[e.to], e.to});
          }
        }
    }
    for (int i = 0; i < (N); i++) pi[i] = min(pi[i] + dist[i], INF);
  }
  pair<int64_t, int64_t> maxflow(int s, int t) {
    int64_t totflow = 0, totcost = 0;
    while (path(s), seen[t]) {
      int64_t fl = INF;
      for (edge* x = par[t]; x; x = par[x->from])
        fl = min(fl, x->cap - x->flow);
      totflow += fl;
      for (edge* x = par[t]; x; x = par[x->from]) {
        x->flow += fl;
        ed[x->to][x->rev].flow -= fl;
      }
    }
    for (int i = 0; i < (N); i++)
      for (edge& e : ed[i]) totcost += e.cost * e.flow;
    return {totflow, totcost / 2};
  }
  // If some costs can be negative, call this before maxflow:
  void setpi(int s) {  // (otherwise, leave this out)
    fill(begin(pi), end(pi), INF);
    pi[s] = 0;
    int it = N, ch = 1;
    int64_t v;
    while (ch-- && it--)
      for (int i = 0; i < (N); i++)
        if (pi[i] != INF)
          for (edge& e : ed[i])
            if (e.cap)
              if ((v = pi[i] + e.cost) < pi[e.to])
                pi[e.to] = v, ch = 1;
    assert(it >= 0);  // negative cost cycle
  }
};
