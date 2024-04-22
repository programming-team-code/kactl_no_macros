/**
 * Author: Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: Calculates all-pairs shortest path in a directed graph that might have negative edge weights.
 * Input is an distance matrix $m$, where $m[i][j] = \texttt{inf}$ if $i$ and $j$ are not adjacent.
 * As output, $m[i][j]$ is set to the shortest distance between $i$ and $j$, \texttt{inf} if no path,
 * or \texttt{-inf} if the path goes through a negative-weight cycle.
 * Time: O(N^3)
 * Status: slightly tested
 */
const int64_t inf = 1LL << 62;
void floydWarshall(vector<vector<int64_t>>& m) {
  int n = (int)(m).size();
  for (int i = 0; i < (n); i++) m[i][i] = min(m[i][i], 0LL);
  for (int k = 0; k < (n); k++)
    for (int i = 0; i < (n); i++)
      for (int j = 0; j < (n); j++)
        if (m[i][k] != inf && m[k][j] != inf) {
          auto newDist = max(m[i][k] + m[k][j], -inf);
          m[i][j] = min(m[i][j], newDist);
        }
  for (int k = 0; k < (n); k++)
    if (m[k][k] < 0)
      for (int i = 0; i < (n); i++)
        for (int j = 0; j < (n); j++)
          if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}
