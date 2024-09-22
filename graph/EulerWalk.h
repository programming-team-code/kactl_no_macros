/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle
 * algorithm. Input should be a vector of (dest, global
 * edge index), where for undirected graphs,
 * forward/backward edges have the same index. Returns a
 * list of nodes in the Eulerian path/cycle with src at
 * both start and end, or empty list if no cycle/path
 * exists. To get edge indices back, add .second to s and
 * ret. Time: O(V + E) Status: stress-tested
 */
vector<int> eulerWalk(vector<vector<pair<int, int>>>& gr,
  int nedges, int src = 0) {
  int n = (int)(gr).size();
  vector<int> D(n), its(n), eu(nedges), ret, s = {src};
  D[src]++; // to allow Euler paths, not just cycles
  while (!s.empty()) {
    int x = s.back(), y, e, &it = its[x],
        end = (int)(gr[x]).size();
    if (it == end) {
      ret.push_back(x);
      s.pop_back();
      continue;
    }
    tie(y, e) = gr[x][it++];
    if (!eu[e]) {
      D[x]--, D[y]++;
      eu[e] = 1;
      s.push_back(y);
    }
  }
  for (int x : D)
    if (x < 0 || (int)(ret).size() != nedges + 1)
      return {};
  return {ret.rbegin(), ret.rend()};
}
