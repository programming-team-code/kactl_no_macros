/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite
 * graph. The size is the same as the size of a maximum
 * matching, and the complement is a maximum independent
 * set. Status: stress-tested
 */
/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Simple bipartite matching algorithm. Graph
 * $g$ should be a list of neighbors of the left partition,
 * and $btoa$ should be a vector full of -1's of the same
 * size as the right partition. Returns the size of the
 * matching. $btoa[i]$ will be the match for vertex $i$ on
 * the right side, or $-1$ if it's not matched. Time: O(VE)
 * Usage: vi btoa(m, -1); dfsMatching(g, btoa);
 * Status: works
 */
bool find(int j, vector<vector<int>>& g, vector<int>& btoa,
  vector<int>& vis) {
  if (btoa[j] == -1) return 1;
  vis[j] = 1;
  int di = btoa[j];
  for (int e : g[di])
    if (!vis[e] && find(e, g, btoa, vis)) {
      btoa[e] = di;
      return 1;
    }
  return 0;
}
int dfsMatching(vector<vector<int>>& g,
  vector<int>& btoa) {
  vector<int> vis;
  for (int i = 0; i < ((int)(g).size()); i++) {
    vis.assign((int)(btoa).size(), 0);
    for (int j : g[i])
      if (find(j, g, btoa, vis)) {
        btoa[j] = i;
        break;
      }
  }
  return (int)(btoa).size() -
    (int)count(begin(btoa), end(btoa), -1);
}
vector<int> cover(vector<vector<int>>& g, int n, int m) {
  vector<int> match(m, -1);
  int res = dfsMatching(g, match);
  vector<bool> lfound(n, true), seen(m);
  for (int it : match)
    if (it != -1) lfound[it] = false;
  vector<int> q, cover;
  for (int i = 0; i < (n); i++)
    if (lfound[i]) q.push_back(i);
  while (!q.empty()) {
    int i = q.back();
    q.pop_back();
    lfound[i] = 1;
    for (int e : g[i])
      if (!seen[e] && match[e] != -1) {
        seen[e] = true;
        q.push_back(match[e]);
      }
  }
  for (int i = 0; i < (n); i++)
    if (!lfound[i]) cover.push_back(i);
  for (int i = 0; i < (m); i++)
    if (seen[i]) cover.push_back(n + i);
  assert((int)(cover).size() == res);
  return cover;
}
