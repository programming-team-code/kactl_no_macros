/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 */
struct AhoCorasick {
  enum { alpha = 26,
         first = 'A' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  void insert(string& s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int& m = N[n].next[c - first];
      if (m == -1) {
        n = m = (int)(N).size();
        N.emplace_back(-1);
      } else n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
  }
  AhoCorasick(vector<string>& pat) : N(1, -1) {
    for (int i = 0; i < ((int)(pat).size()); i++) insert(pat[i], i);
    N[0].back = (int)(N).size();
    N.emplace_back(0);
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      for (int i = 0; i < (alpha); i++) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1) ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }
  vector<int> find(string word) {
    int n = 0;
    vector<int> res;  // ll count = 0;
    for (char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
      // count += N[n].nmatches;
    }
    return res;
  }
  vector<vector<int>> findAll(vector<string>& pat, string word) {
    vector<int> r = find(word);
    vector<vector<int>> res((int)(word).size());
    for (int i = 0; i < ((int)(word).size()); i++) {
      int ind = r[i];
      while (ind != -1) {
        res[i - (int)(pat[ind]).size() + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
};
