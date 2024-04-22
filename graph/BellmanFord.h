/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
const int64_t inf = LLONG_MAX;
struct Ed {
  int a, b, w, s() { return a < b ? a : -a; }
};
struct Node {
  int64_t dist = inf;
  int prev = -1;
};
void bellmanFord(vector<Node>& nodes, vector<Ed>& eds, int s) {
  nodes[s].dist = 0;
  sort(begin(eds), end(eds), [](Ed a, Ed b) { return a.s() < b.s(); });
  int lim = (int)(nodes).size() / 2 + 2;  // /3+100 with shuffled vertices
  for (int i = 0; i < (lim); i++)
    for (Ed ed : eds) {
      Node cur = nodes[ed.a], &dest = nodes[ed.b];
      if (abs(cur.dist) == inf) continue;
      int64_t d = cur.dist + ed.w;
      if (d < dest.dist) {
        dest.prev = ed.a;
        dest.dist = (i < lim - 1 ? d : -inf);
      }
    }
  for (int i = 0; i < (lim); i++)
    for (Ed e : eds) {
      if (nodes[e.a].dist == -inf)
        nodes[e.b].dist = -inf;
    }
}
