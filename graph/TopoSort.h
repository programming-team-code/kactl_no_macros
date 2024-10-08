/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented
 * graph. Output is an ordering of vertices, such that
 * there are edges only from left to right. If there are
 * cycles, the returned list will have size smaller than
 * $n$ -- nodes reachable from cycles will not be returned.
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
vector<int> topoSort(const vector<vector<int>>& gr) {
  vector<int> indeg((int)(gr).size()), ret;
  for (auto& li : gr)
    for (int x : li) indeg[x]++;
  queue<int>
    q; // use priority_queue for lexic. largest ans.
  for (int i = 0; i < ((int)(gr).size()); i++)
    if (indeg[i] == 0) q.push(i);
  while (!q.empty()) {
    int i = q.front(); // top() for priority queue
    ret.push_back(i);
    q.pop();
    for (int x : gr[i])
      if (--indeg[x] == 0) q.push(x);
  }
  return ret;
}
