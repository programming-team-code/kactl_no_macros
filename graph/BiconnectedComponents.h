/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
vector<int> num, st;
vector<vector<pair<int, int>>> ed;
int Time;
template <class F>
int dfs(int at, int par, F& f) {
  int me = num[at] = ++Time, top = me;
  for (auto [y, e] : ed[at])
    if (e != par) {
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.push_back(e);
      } else {
        int si = (int)(st).size();
        int up = dfs(y, e, f);
        top = min(top, up);
        if (up == me) {
          st.push_back(e);
          f(vector<int>(st.begin() + si, st.end()));
          st.resize(si);
        } else if (up < me) st.push_back(e);
        else { /* e is a bridge */ }
      }
    }
  return top;
}
template <class F>
void bicomps(F f) {
  num.assign((int)(ed).size(), 0);
  for (int i = 0; i < ((int)(ed).size()); i++)
    if (!num[i]) dfs(i, -1, f);
}
