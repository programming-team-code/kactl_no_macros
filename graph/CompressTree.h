/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree and a subset S of
 * nodes, compute the minimal subtree that contains all the
 * nodes by adding all (at most $|S|-1$) pairwise LCA's and
 * compressing edges. Returns a list of (par, orig\_index)
 * representing a tree rooted at 0. The root points to
 * itself. Time: $O(|S| \log |S|)$ Status: Tested at
 * CodeForces
 */
/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common
 * ancestors in a tree (with 0 as root). C should be an
 * adjacency list of the tree, either directed or
 * undirected. Time: $O(N \log N + Q)$ Status:
 * stress-tested
 */
/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
template<class T> struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V): jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= (int)(V).size();
         pw *= 2, ++k) {
      jmp.emplace_back((int)(V).size() - pw * 2 + 1);
      for (int j = 0; j < ((int)(jmp[k]).size()); j++)
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};
struct LCA {
  int T = 0;
  vector<int> time, path, ret;
  RMQ<int> rmq;
  LCA(vector<vector<int>>& C):
    time((int)(C).size()), rmq((dfs(C, 0, -1), ret)) {}
  void dfs(vector<vector<int>>& C, int v, int par) {
    time[v] = T++;
    for (int y : C[v])
      if (y != par) {
        path.push_back(v), ret.push_back(time[v]);
        dfs(C, y, v);
      }
  }
  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  // dist(a,b){return depth[a] + depth[b] -
  // 2*depth[lca(a,b)];}
};
typedef vector<pair<int, int>> vpi;
vpi compressTree(LCA& lca, const vector<int>& subset) {
  static vector<int> rev;
  rev.resize((int)(lca.time).size());
  vector<int> li = subset, &T = lca.time;
  auto cmp = [&](int a, int b) { return T[a] < T[b]; };
  sort(begin(li), end(li), cmp);
  int m = (int)(li).size() - 1;
  for (int i = 0; i < (m); i++) {
    int a = li[i], b = li[i + 1];
    li.push_back(lca.lca(a, b));
  }
  sort(begin(li), end(li), cmp);
  li.erase(unique(begin(li), end(li)), li.end());
  for (int i = 0; i < ((int)(li).size()); i++)
    rev[li[i]] = i;
  vpi ret = {pair<int, int>(0, li[0])};
  for (int i = 0; i < ((int)(li).size() - 1); i++) {
    int a = li[i], b = li[i + 1];
    ret.emplace_back(rev[lca.lca(a, b)], b);
  }
  return ret;
}
